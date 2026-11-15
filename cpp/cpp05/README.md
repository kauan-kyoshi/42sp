# CPP05 — Repetição e Exceções

## Visão geral do módulo

O CPP05 constrói, exercício após exercício, um pequeno sistema burocrático. O tema serve para apresentar exceções em C++ e, em seguida, combiná-las com colaboração entre classes, herança, classes abstratas, polimorfismo e alocação dinâmica.

Cada pasta é um programa independente e cumulativo. Isso significa que o `ex01` contém uma nova versão de `Bureaucrat`, o `ex02` contém outra versão adaptada para `AForm` e o `ex03` repete as classes anteriores antes de acrescentar `Intern`. Os exercícios não são compilados juntos.

A progressão geral é:

```text
ex00: Bureaucrat
  └── mantém um grau válido e lança exceções

ex01: Bureaucrat ↔ Form
  └── dois objetos colaboram para assinar um formulário

ex02: Bureaucrat → AForm → formulários concretos
  └── herança e polimorfismo permitem executar ações diferentes

ex03: Intern → cria AForm*
  └── a criação do tipo concreto é escolhida em tempo de execução
```

## Comparação entre os exercícios

| Exercício | O que é acrescentado | Problema principal | Conceitos centrais |
| --- | --- | --- | --- |
| `ex00` | Classe `Bureaucrat` | Manter o grau sempre entre 1 e 150 | Exceções, invariantes, encapsulamento, Forma Canônica Ortodoxa, sobrecarga de `<<` |
| `ex01` | Classe `Form` e `signForm()` | Autorizar uma ação de um objeto com base no estado de outro | Colaboração entre classes, dependência circular, declarações antecipadas, estado mutável e membros constantes |
| `ex02` | `AForm` abstrata e três subclasses | Compartilhar validações e executar comportamentos diferentes pela mesma interface | Herança, função virtual pura, polimorfismo, destrutor virtual, Template Method, arquivos e comportamento aleatório |
| `ex03` | Classe `Intern` e `makeForm()` | Escolher e construir uma classe concreta a partir de uma string | Funções criadoras, ponteiros para função, alocação dinâmica, propriedade de memória e retorno polimórfico |

## ex00 — Um objeto que protege suas próprias regras

O primeiro exercício apresenta `Bureaucrat`. Um burocrata possui:

- um nome constante;
- um grau entre 1 e 150;
- operações para subir e descer na hierarquia;
- exceções para impedir graus fora do intervalo.

O detalhe mais importante é que a ordem numérica é inversa à posição hierárquica: grau 1 é o mais alto e grau 150 é o mais baixo. Portanto, `incrementGrade()` promove o burocrata diminuindo o número, enquanto `decrementGrade()` o rebaixa aumentando o número.

### Conceito: invariante de classe

Uma invariante é uma condição que deve continuar verdadeira durante toda a vida útil de um objeto. Para `Bureaucrat`, ela pode ser escrita assim:

```text
1 <= grade <= 150
```

O construtor valida o valor inicial. Depois disso, `grade` é privado e só pode ser alterado por métodos que verificam os limites. Desse modo, um objeto construído com sucesso nunca deveria ficar inválido.

As verificações acontecem antes da alteração. Se um burocrata de grau 1 for promovido, `GradeTooHighException` é lançada e o grau continua sendo 1. Essa ordem oferece uma garantia importante: uma operação que falha não deixa o objeto parcialmente modificado.

### Conceito: exceções

`GradeTooHighException` e `GradeTooLowException` herdam de `std::exception`. Isso permite dois níveis de tratamento:

```cpp
catch (const Bureaucrat::GradeTooHighException &e)
```

quando é necessário distinguir a causa exata, ou:

```cpp
catch (const std::exception &e)
```

quando basta tratar qualquer erro compatível com a interface padrão. O método virtual `what()` fornece uma descrição do problema.

O fluxo de uma exceção é diferente de um retorno comum. `throw` interrompe a função imediatamente e procura um `catch` compatível na pilha de chamadas. Se a construção lança uma exceção, o objeto não chega a existir como uma instância válida para o chamador.

### Conceito: membros constantes e Forma Canônica Ortodoxa

O nome é `const`, então precisa ser definido na lista de inicialização do construtor. O construtor de cópia pode inicializar o nome de um novo objeto, mas o operador de atribuição trabalha sobre um objeto que já foi construído. Por isso, a atribuição copia apenas o grau e preserva o nome do destino.

Essa diferença demonstra que construção e atribuição são operações distintas:

```cpp
Bureaucrat copy(original);       // novo objeto: copia nome e grau
Bureaucrat target("B", 100);
target = original;              // objeto existente: preserva "B"
```

O exercício também pratica a Forma Canônica Ortodoxa: construtor padrão, construtor de cópia, operador de atribuição e destrutor.

### Conceito: sobrecarga de operador

`operator<<` permite imprimir um burocrata com a sintaxe normal dos fluxos:

```cpp
std::cout << bureaucrat << std::endl;
```

Ele é uma função livre e acessa o objeto pelos getters públicos. Assim, não precisa ser `friend`, palavra-chave proibida pelas regras gerais do módulo.

## ex01 — Dois objetos passam a colaborar

O segundo exercício preserva `Bureaucrat` e acrescenta `Form`. Um formulário possui:

- nome constante;
- estado indicando se está assinado;
- grau constante necessário para assinatura;
- grau constante necessário para execução.

Neste ponto, o requisito de execução ainda é apenas armazenado e exibido. A execução real aparece no `ex02`.

### Diferença principal em relação ao ex00

No `ex00`, todas as regras pertencem a um único objeto. No `ex01`, uma operação depende de dois objetos: o formulário conhece o grau necessário e o burocrata fornece o grau disponível.

O formulário é responsável por proteger seu próprio estado. Por isso, a decisão final fica em:

```cpp
form.beSigned(bureaucrat);
```

Se o grau for suficiente, `signedStatus` passa a `true`. Se for insuficiente, o formulário lança `Form::GradeTooLowException` e continua não assinado.

`Bureaucrat::signForm()` funciona como uma camada de interação: solicita a assinatura, captura o erro e imprime o resultado. A responsabilidade fica dividida assim:

| Responsabilidade | Classe |
| --- | --- |
| Saber o grau do funcionário | `Bureaucrat` |
| Saber o requisito e o estado da assinatura | `Form` |
| Decidir se pode ser assinado | `Form::beSigned()` |
| Relatar sucesso ou falha da tentativa | `Bureaucrat::signForm()` |

### Conceito: comparação de autoridade

Como grau 1 é superior ao grau 150, a assinatura falha quando:

```cpp
bureaucrat.getGrade() > gradeToSign
```

Um burocrata de grau exatamente igual ao requisito pode assinar. A comparação usa `>` e não `>=`.

### Conceito: dependências entre cabeçalhos

`Bureaucrat` precisa mencionar `Form`, e `Form` precisa mencionar `Bureaucrat`. Incluir os dois cabeçalhos diretamente um no outro criaria uma dependência circular desnecessária.

As interfaces usam declarações antecipadas:

```cpp
class Form;
class Bureaucrat;
```

Isso é suficiente porque os métodos recebem referências. Os arquivos `.cpp`, que precisam chamar os métodos do outro tipo, incluem as definições completas. O resultado são cabeçalhos independentes e uma relação de dependência mais clara.

### Conceito: estado constante e estado mutável

Nome e requisitos definem a identidade e as regras permanentes do formulário. O estado de assinatura pode mudar. Na atribuição entre formulários, somente esse estado mutável é copiado; os membros constantes do destino permanecem iguais.

Esse comportamento reforça a diferença entre copiar um novo objeto e atribuir a um objeto já existente, vista inicialmente no `ex00`.

## ex02 — De um formulário único para uma família polimórfica

O terceiro estágio é a maior mudança estrutural do módulo. `Form` passa a se chamar `AForm` e se torna abstrata. Três classes concretas herdam dela:

| Classe | Assinar | Executar | Ação |
| --- | ---: | ---: | --- |
| `ShrubberyCreationForm` | 145 | 137 | Cria `<target>_shrubbery` com uma árvore ASCII |
| `RobotomyRequestForm` | 72 | 45 | Faz ruídos e relata sucesso ou falha da robotomia |
| `PresidentialPardonForm` | 25 | 5 | Informa que o alvo foi perdoado por Zaphod Beeblebrox |

### Diferença principal em relação ao ex01

No `ex01`, existe apenas um tipo de formulário e ele não executa uma ação. No `ex02`, todos os formulários compartilham regras de assinatura e autorização, mas cada um executa algo diferente.

Colocar toda a lógica em uma única classe exigiria condicionais para descobrir o tipo do formulário. A herança permite representar o que é comum na base e o que varia nas subclasses.

### Conceito: classe abstrata

`AForm` declara uma função virtual pura:

```cpp
virtual void executeAction() const = 0;
```

O `= 0` torna `AForm` abstrata: ela descreve a interface e o estado comum, mas não pode ser instanciada diretamente. Cada classe concreta precisa implementar sua própria ação.

O nome `AForm` comunica essa intenção. O prefixo `A` é uma convenção usada neste projeto para indicar uma classe abstrata.

### Conceito: polimorfismo dinâmico

`Bureaucrat::executeForm()` recebe `const AForm &`. A referência pode representar qualquer uma das três subclasses. Quando `executeAction()` é chamada, C++ seleciona em tempo de execução a implementação correspondente ao tipo real do objeto.

```text
AForm& apontando para ShrubberyCreationForm
                    └── chama a ação de arbustos

AForm& apontando para RobotomyRequestForm
                    └── chama a ação de robotomia

AForm& apontando para PresidentialPardonForm
                    └── chama a ação de perdão
```

O burocrata não precisa conhecer cada classe concreta. Ele trabalha somente com o contrato de `AForm`. Isso reduz o acoplamento e permite acrescentar novos formulários sem mudar `executeForm()`.

### Conceito: validação comum e Template Method

`AForm::execute()` organiza um algoritmo fixo:

1. Verificar se o formulário está assinado.
2. Verificar se o executor possui grau suficiente.
3. Chamar a ação concreta.

Esse desenho é conhecido como Template Method: a classe-base controla a sequência e delega uma etapa variável para uma função virtual.

Manter as validações na base evita duplicá-las nas três subclasses. Também impede divergências, como uma classe verificar o grau antes da assinatura e outra esquecer uma das regras.

### Conceito: ordem das validações

Um formulário não assinado lança `FormNotSignedException`, independentemente do grau do executor. Depois da assinatura, um executor sem autoridade provoca `GradeTooLowException`. Somente após as duas verificações a ação pode causar efeitos externos.

Essa ordem é especialmente importante para `ShrubberyCreationForm`: o arquivo só deve ser criado depois que todas as permissões forem confirmadas.

### Conceito: efeitos e recursos externos

Cada formulário demonstra um tipo de comportamento:

- `ShrubberyCreationForm` usa `std::ofstream`, verifica se o arquivo abriu e se a escrita permaneceu válida. Como o projeto usa C++98, o nome construído com `std::string` é passado por `c_str()`.
- `RobotomyRequestForm` usa `std::rand() % 2` para escolher entre dois resultados possíveis. O teste deve aceitar tanto sucesso quanto falha.
- `PresidentialPardonForm` produz uma ação determinística, imprimindo a mensagem exigida.

### Conceito: destrutor virtual

`AForm` possui destrutor virtual. Isso se torna essencial quando um objeto derivado é manipulado por um ponteiro da base:

```cpp
AForm *form = new RobotomyRequestForm("Bender");
delete form;
```

O destrutor virtual garante que a destruição percorra o tipo concreto corretamente. Sem ele, apagar um objeto derivado por `AForm*` teria comportamento indefinido.

## ex03 — A criação dos objetos também vira uma abstração

O último exercício mantém a hierarquia do `ex02` e adiciona `Intern`. O estagiário recebe o nome textual de um formulário e seu alvo:

```cpp
AForm *form = intern.makeForm("robotomy request", "Bender");
```

Se o nome for reconhecido, `makeForm()` cria o tipo concreto correspondente e o devolve como `AForm*`. Se não for reconhecido, imprime um erro e retorna `0`.

### Diferença principal em relação ao ex02

No `ex02`, o próprio código chamador escolhe a classe concreta:

```cpp
RobotomyRequestForm form("Bender");
```

No `ex03`, o chamador fornece dados e deixa a escolha com `Intern`:

```cpp
AForm *form = intern.makeForm(name, target);
```

Essa mudança separa a criação do uso. Depois de receber o ponteiro, o restante do programa pode assinar e executar o objeto somente pela interface `AForm`, sem precisar descobrir novamente seu tipo concreto.

### Conceito: função criadora

As três funções internas de criação possuem a mesma assinatura:

```cpp
typedef AForm *(*FormCreator)(const std::string &target);
```

O código mantém um array de nomes e outro de funções criadoras. A mesma posição representa um par:

| Nome recebido | Função | Objeto criado |
| --- | --- | --- |
| `shrubbery creation` | `createShrubbery` | `ShrubberyCreationForm` |
| `robotomy request` | `createRobotomy` | `RobotomyRequestForm` |
| `presidential pardon` | `createPardon` | `PresidentialPardonForm` |

Um laço procura o nome e chama a função correspondente. Essa tabela evita uma cadeia longa de `if/else if/else`, explicitamente rejeitada pelo subject, e concentra o mapeamento em uma estrutura legível.

Esse desenho é uma forma simples de fábrica: um componente recebe uma descrição e devolve um objeto por uma interface comum.

### Conceito: alocação dinâmica e propriedade

As funções criadoras usam `new`, porque o objeto precisa continuar existindo depois que `makeForm()` retorna. Um objeto local seria destruído ao sair da função e não poderia ter seu endereço devolvido com segurança.

O ponteiro retornado transfere ao chamador a responsabilidade pela memória:

```cpp
AForm *form = intern.makeForm(name, target);
if (form != 0)
{
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;
}
```

Cada `new` bem-sucedido precisa corresponder a um `delete`. O destrutor virtual de `AForm`, introduzido no `ex02`, torna essa liberação polimórfica segura.

Quando o nome é inválido, nenhuma alocação ocorre e `0` é retornado. `delete` em um ponteiro nulo é permitido, mas conferir o ponteiro antes de desreferenciá-lo é obrigatório.

### Conceito: classe sem estado

`Intern` não possui atributos. Ainda assim, implementa construtor padrão, construtor de cópia, operador de atribuição e destrutor para seguir a Forma Canônica Ortodoxa. Como não há estado, cópia e atribuição não têm dados para transferir.

Isso mostra que a forma canônica descreve a interface de ciclo de vida de uma classe, mas o trabalho realizado por cada operação depende dos recursos e atributos que ela possui.

## A progressão conceitual completa

O módulo pode ser entendido como quatro níveis de responsabilidade:

### 1. Proteger um objeto

O `ex00` ensina a manter um objeto válido. Construtores e métodos conferem os limites, e exceções comunicam operações impossíveis.

### 2. Coordenar objetos

O `ex01` ensina que cada classe deve controlar seu próprio estado. O burocrata solicita; o formulário decide e altera sua assinatura.

### 3. Generalizar comportamentos

O `ex02` separa regras comuns de ações variáveis. `AForm` define o contrato e o fluxo; as subclasses fornecem as ações concretas.

### 4. Generalizar a criação

O `ex03` remove do chamador a obrigação de selecionar diretamente a classe concreta. `Intern` transforma um nome em um objeto polimórfico, e o chamador passa a gerenciar sua duração.

O fluxo final reúne tudo:

```text
nome + alvo
    │
    ▼
Intern::makeForm()
    │ cria com new
    ▼
AForm* apontando para uma classe concreta
    │
    ├── Bureaucrat::signForm()
    │       └── AForm::beSigned() valida o grau
    │
    ├── Bureaucrat::executeForm()
    │       └── AForm::execute()
    │             ├── verifica assinatura
    │             ├── verifica grau
    │             └── executeAction() virtual
    │
    ▼
delete por AForm* com destrutor virtual
```

## Conceitos que atravessam todos os exercícios

### Encapsulamento

Os atributos ficam privados. As classes expõem operações que preservam suas regras, em vez de permitir alterações diretas. Os getters são `const`, pois consultar não deve modificar o objeto.

### Segurança diante de falhas

As validações precedem as mudanças e os efeitos. Uma promoção inválida não altera o grau; uma assinatura negada não muda o formulário; uma execução sem autorização não cria arquivos nem imprime o resultado da ação.

### Uso de referências constantes

Parâmetros como `const Bureaucrat &` e `const AForm &` evitam cópias e expressam que a função não pretende modificar o argumento. Quando uma operação precisa alterar o formulário, como `signForm()`, a referência não é constante.

### Separação entre interface e implementação

Os `.hpp` declaram o contrato público e incluem suas próprias dependências. Os `.cpp` contêm as implementações. As proteções de inclusão evitam definições duplicadas.

### Forma Canônica Ortodoxa

Do `ex00` ao `ex03`, as classes não excepcionais implementam as quatro operações canônicas. Membros constantes exigem atenção especial: podem ser inicializados na construção, mas não atribuídos posteriormente.

### C++98

Todo o módulo compila com:

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

Isso exclui facilidades modernas como `nullptr`, `override`, lambdas e smart pointers. Por isso o `ex03` usa `0`, ponteiros de função tradicionais e gerenciamento manual com `new` e `delete`.

## Como estudar o código

Uma ordem útil para acompanhar a evolução é:

1. Ler `ex00/Bureaucrat.hpp` e identificar a invariante do grau.
2. Seguir no `.cpp` onde cada exceção é lançada e observar que o estado só muda depois da validação.
3. Comparar o `Bureaucrat` do `ex00` com o do `ex01` e localizar apenas a nova colaboração com `Form`.
4. Ler `Form::beSigned()` e depois voltar a `Bureaucrat::signForm()` para enxergar quem decide e quem relata.
5. No `ex02`, começar por `AForm::execute()` antes das subclasses. Essa função explica o fluxo comum.
6. Abrir cada `executeAction()` e comparar somente a parte que varia.
7. No `ex03`, seguir `Intern::makeForm()` desde a string até o `AForm*` retornado.
8. Terminar no `main.cpp`, observando o ciclo completo: criar, verificar o ponteiro, assinar, executar e liberar.

Os READMEs dentro de cada exercício detalham seus testes e a implementação específica:

- [`ex00/README.md`](ex00/README.md)
- [`ex01/README.md`](ex01/README.md)
- [`ex02/README.md`](ex02/README.md)
- [`ex03/README.md`](ex03/README.md)
