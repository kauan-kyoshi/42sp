# CPP05 — ex00: Bureaucrat

## 1. O que é o exercício

O exercício apresenta o tratamento de exceções em C++ por meio de uma classe que representa um burocrata. A classe `Bureaucrat` armazena um nome constante e uma classificação, chamada `grade` no código. O objetivo é impedir a criação ou a alteração de um burocrata para uma classificação inválida e permitir que quem utiliza a classe trate esses erros com `try` e `catch`.

A classificação precisa estar entre **1 e 150**, incluindo os dois extremos. O número indica a posição na hierarquia: **1 é a classificação mais alta e 150 é a mais baixa**.

| Operação | Exemplo válido | Tentativa inválida |
| --- | --- | --- |
| Construir | Nome `Ana`, grau `42` | Grau `0` ou `151` |
| Promover: `incrementGrade()` | Grau `3` passa a `2` | Promover alguém no grau `1` |
| Rebaixar: `decrementGrade()` | Grau `3` passa a `4` | Rebaixar alguém no grau `150` |

Os nomes das funções se referem à classificação hierárquica. Por isso, incrementar a classificação diminui o valor numérico de `grade`.

Os erros possuem tipos distintos:

- `Bureaucrat::GradeTooHighException`: o grau solicitado representa uma posição acima do permitido, isto é, um número menor que `1`.
- `Bureaucrat::GradeTooLowException`: o grau solicitado representa uma posição abaixo do permitido, isto é, um número maior que `150`.

Essas classes herdam publicamente de `std::exception`. Isso permite capturar cada tipo específico ou usar `catch (const std::exception &e)` para tratar ambos. A função `e.what()` fornece uma descrição do erro.

O nome pode ser consultado, mas não alterado após a construção. A classificação também só pode ser consultada diretamente: as alterações passam pelos métodos de promoção e rebaixamento, que preservam os limites.

O exercício exige getters (`getName()` e `getGrade()`), a Forma Canônica Ortodoxa e uma sobrecarga de `operator<<`. Nesta versão traduzida do subject, a impressão segue este formato:

```text
Ana, burocrata com classificação 42.
```

A compilação utiliza `c++ -Wall -Wextra -Werror -std=c++98`. As regras gerais proíbem bibliotecas externas, recursos de C++11 em diante, contêineres STL, `<algorithm>`, `using namespace`, `friend`, `*printf`, `*alloc` e `free`. As implementações ficam nos arquivos `.cpp`, e o cabeçalho tem proteção contra inclusão dupla. As classes de exceção estão dispensadas da Forma Canônica Ortodoxa.

## 2. Como testar e o que é esperado

### Compilar e executar

No terminal, execute:

```bash
cd /home/kyoshi/42/42sp/cpp/cpp05/ex00
make
./bureaucrat
```

O `make` compila `main.cpp` e `Bureaucrat.cpp` em arquivos `.o` e depois gera o executável `bureaucrat`. A compilação deve terminar sem avisos ou erros. O programa não precisa de argumentos nem de entrada pelo teclado.

Em um ambiente com `int` de 32 bits, a saída esperada é:

```text
0: Classificacao alta demais
151: Classificacao baixa demais
-2147483648: Classificacao alta demais
2147483647: Classificacao baixa demais
Classificacao alta demais
Classificacao baixa demais
Ana, burocrata com classificação 42.
Todos os testes passaram.
```

Os números das linhas de valores extremos vêm de `INT_MIN` e `INT_MAX`, definidos em `<climits>`. Eles podem variar conforme a representação de `int` da plataforma.

As mensagens de classificação inválida são **resultados esperados dos testes**: o programa provoca os erros e captura as exceções. Uma exceção capturada permite continuar a execução. A última linha só é alcançada se todas as verificações anteriores passarem na compilação padrão do Makefile.

### O que cada grupo de testes verifica

| Grupo no `main.cpp` | Verificações |
| --- | --- |
| `testInvalidGrade()` | Construções com `0`, `151`, `INT_MIN` e `INT_MAX` lançam o tipo correto de exceção. |
| `testLimits()` | Promoção de `2` para `1`, rebaixamento de `149` para `150`, rejeição de alterações além desses limites e preservação do grau após a falha. Também verifica o retorno de `1` para `2` e de `150` para `149`. |
| `testCanonicalForm()` | Grau padrão `150`, cópia de nome e grau, independência da cópia, atribuição que preserva o nome do destino, autoatribuição e texto produzido por `operator<<` usando um objeto constante. |

Os testes usam `assert`, de `<cassert>`. Se a condição for falsa, a execução é interrompida e uma mensagem indica a verificação que falhou. Se for verdadeira, a execução continua sem imprimir nada. Portanto, vários testes bem-sucedidos são silenciosos.

Não adicione `-DNDEBUG` ao executar esses testes: essa macro desativa os `assert`. O Makefile fornecido não a define.

Para consultar o código de saída imediatamente após executar o programa:

```bash
echo $?
```

O resultado esperado é `0`. Ele deve ser considerado junto com a mensagem final e os `assert` ativos.

### Verificar o Makefile

Execute `make` novamente sem modificar os arquivos. Ele deve informar que não há trabalho a fazer, sem recompilar nem ligar o executável novamente.

Os demais alvos são:

```bash
make clean
make fclean
make re
```

- `clean`: remove somente os objetos `.o`.
- `fclean`: remove os objetos e o executável.
- `re`: faz a limpeza completa e recompila.

O cabeçalho `Bureaucrat.hpp` é dependência dos objetos. Quando ele muda, o próximo `make` recompila os fontes para refletir a nova declaração da classe.

## 3. Fluxo do código e decisões de implementação

### Organização dos arquivos e compilação

`Bureaucrat.hpp` declara a interface: atributos, construtores, operador de atribuição, destrutor, getters, operações de classificação e exceções. Ele inclui `<string>`, `<exception>` e `<ostream>` porque essas dependências são necessárias para entender suas declarações sem depender da ordem de inclusão de outros cabeçalhos.

As diretivas `#ifndef BUREAUCRAT_HPP`, `#define BUREAUCRAT_HPP` e `#endif` impedem que as declarações sejam processadas mais de uma vez na mesma unidade de tradução.

`Bureaucrat.cpp` implementa a interface. Essa separação atende ao subject e permite ler o contrato da classe sem percorrer seus detalhes internos. `main.cpp` reúne os testes, mantendo as verificações separadas da classe.

O Makefile transforma cada `.cpp` em um `.o` e liga os objetos no executável. `-Wall` e `-Wextra` habilitam avisos, `-Werror` transforma avisos em erros e `-std=c++98` seleciona o padrão exigido. O alvo `re` chama `$(MAKE) all` depois da limpeza, garantindo essa ordem mesmo quando o Make é executado com paralelismo.

### Construção e validade do objeto

Ao entrar em `main()`, a primeira chamada é `testInvalidGrade(0)`. Dentro dela, o bloco `try` tenta construir `Bureaucrat invalid("Invalid", grade)`.

O construtor parametrizado começa pela lista de inicialização:

```cpp
Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : name(name), grade(grade)
```

À esquerda dos parênteses estão os membros; dentro deles estão os parâmetros usados para inicializá-los. O membro `name` precisa ser inicializado dessa maneira porque é `const`: não seria possível deixá-lo para uma atribuição no corpo do construtor.

Depois da inicialização, o corpo verifica o intervalo. Se o grau for menor que `1`, lança `GradeTooHighException`; se for maior que `150`, lança `GradeTooLowException`. O `throw` interrompe o fluxo normal. A construção não termina e nenhum objeto `Bureaucrat` utilizável é entregue ao chamador. Os membros já construídos são destruídos automaticamente; o destrutor de `Bureaucrat` não é chamado para essa construção incompleta.

Se o grau for válido, o construtor termina normalmente. Assim, todo objeto construído com sucesso respeita a regra central da classe: `1 <= grade && grade <= 150`.

O construtor padrão escolhe o nome `"Default"` e o grau `150`. Esses valores são uma decisão da implementação, pois o exercício não define quais devem ser os valores padrão. Eles permitem fornecer a Forma Canônica Ortodoxa com um estado inicial válido.

### Exceções e retorno aos testes

Quando ocorre um `throw`, a execução procura um `catch` compatível. Em `testInvalidGrade()`, os dois tipos específicos têm tratamentos separados. Cada tratamento verifica se a direção do erro é a esperada, marca `caught` como verdadeiro e imprime `e.what()`.

O `assert(caught)` após os tratamentos verifica que uma exceção realmente ocorreu. Isso evita considerar o teste aprovado se o construtor aceitar silenciosamente um grau inválido.

As classes de exceção estão declaradas dentro de `Bureaucrat`, o que explica os nomes completos como `Bureaucrat::GradeTooHighException`. O escopo associa os erros à classe responsável por eles.

Cada `what()` retorna um literal de texto com duração válida durante toda a execução. A assinatura `const char *what() const throw()` corresponde ao contrato de `std::exception` em C++98: `const` permite consultar uma exceção constante e `throw()` declara que essa função não lança exceções. As definições ficam no `.cpp`, como as demais funções.

Os blocos `catch` recebem uma referência constante. Isso evita copiar a exceção e permite chamar seu método virtual `what()` preservando o comportamento do tipo concreto. Em `testLimits()`, a captura por `const std::exception &` demonstra que a herança pública permite tratar ambos os erros pela interface comum.

### Promoção e rebaixamento

Depois dos quatro testes de construção inválida, `main()` chama `testLimits()`.

`incrementGrade()` verifica primeiro se o grau já é `1`. Nesse caso, lança uma exceção. Caso contrário, executa `--grade`. `decrementGrade()` faz o equivalente no limite `150` e, se permitido, executa `++grade`.

A validação ocorre **antes da alteração** para que uma tentativa inválida deixe o objeto no estado anterior. Não é necessário alterar o grau, perceber o erro e desfazer a mudança. Os testes confirmam que os valores continuam em `1` e `150` depois das falhas.

Essas funções verificam apenas o limite relevante porque os construtores e a interface já garantem graus válidos. Os atributos são privados e não existe setter que aceite qualquer inteiro. A atribuição também recebe outro objeto válido. Essa combinação impede que o código externo quebre a regra da classe por uma alteração direta.

### Cópia, atribuição e destruição

Em seguida, `main()` chama `testCanonicalForm()`. A Forma Canônica Ortodoxa é representada pelo construtor padrão, construtor de cópia, operador de atribuição e destrutor.

O construtor de cópia inicializa um novo objeto com o nome e o grau do original. Como o objeto ainda está sendo criado, é permitido inicializar seu nome constante com o nome de outro burocrata. A cópia possui seus próprios membros; promover a cópia não altera o original.

O operador de atribuição atua sobre um objeto que já existe. Por isso, preserva seu nome constante e copia somente o grau:

```cpp
Bureaucrat original("Ana", 42);
Bureaucrat assigned("Bruno", 100);
assigned = original;
// assigned continua com o nome Bruno e passa ao grau 42.
```

Essa escolha respeita a imutabilidade do nome sem remover o operador exigido pela Forma Canônica Ortodoxa. Não se usa conversão para retirar o `const`, nem reconstrução do objeto para trocar sua identidade.

A condição `this != &other` evita trabalho na autoatribuição. Nesse código, copiar o mesmo inteiro já seria seguro, mas a verificação deixa explícito o tratamento desse caso. O retorno `*this` por referência permite encadear atribuições.

O destrutor tem corpo vazio porque a classe não gerencia recursos manualmente. `std::string` libera seus próprios recursos automaticamente, e `int` não exige limpeza. Os objetos locais são destruídos ao sair de seus respectivos escopos. Não foi necessário usar `new` ou `delete`.

### Consulta e impressão

`getName()` retorna `const std::string &`: a referência evita criar uma cópia do nome e o `const` impede modificá-lo por essa referência. Ela se refere ao membro do objeto, portanto não deve ser usada após a destruição do burocrata. `getGrade()` retorna o inteiro por valor, uma operação simples e barata.

Os dois getters são métodos `const`, pois consultar o estado não precisa alterar o objeto. Isso permite usá-los também em um `const Bureaucrat`.

O operador `<<` é uma função livre porque o operando à esquerda é um fluxo, como `std::cout`. Ele consulta os dados pelos getters públicos, sem precisar de `friend`, e retorna o mesmo fluxo por referência. Assim, esta expressão funciona:

```cpp
std::cout << constant << std::endl;
```

O operador escreve o nome, o texto fixo, o grau e o ponto final. A quebra de linha fica com o chamador, permitindo compor a impressão com outras operações de fluxo. No teste, `std::endl` encerra a linha.

Para validar o texto, `testCanonicalForm()` usa `std::ostringstream`, de `<sstream>`. Esse fluxo recebe a impressão em memória, e `output.str()` permite compará-la com a string esperada. Isso testa o formato diretamente, sem depender apenas de inspeção visual do terminal.

### Encerramento do programa

As funções de teste são `static` porque só precisam ser acessíveis dentro de `main.cpp`. A ordem da execução é:

1. Rejeitar graus inválidos no construtor.
2. Verificar promoções, rebaixamentos e preservação do estado nos limites.
3. Verificar construção padrão, cópia, atribuição, autoatribuição e impressão.
4. Imprimir `Todos os testes passaram.` e retornar `0`.

A implementação mantém a responsabilidade pela validade dentro de `Bureaucrat`, enquanto o `main()` demonstra como o usuário da classe recebe e trata os erros. Isso permite reutilizar a classe nos exercícios seguintes sem depender das funções de teste.
