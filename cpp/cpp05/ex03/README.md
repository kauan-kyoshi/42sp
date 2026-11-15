# CPP05 — ex03: Intern

## 1. O que é o exercício

O último exercício adiciona a classe `Intern`. O estagiário não possui nome, grau nem estado próprio. Sua responsabilidade é criar um dos três formulários concretos a partir de duas strings: o nome do tipo de formulário e seu alvo.

`makeForm()` reconhece exatamente `"shrubbery creation"`, `"robotomy request"` e `"presidential pardon"`. Para um nome válido, aloca a classe correspondente, inicializa o alvo, imprime a criação e devolve um `AForm*`. Para um nome desconhecido, imprime um erro explícito e devolve o ponteiro nulo.

O chamador passa a ser dono do objeto retornado e precisa usar `delete` quando terminar. Isso funciona com segurança porque `AForm` possui destrutor virtual.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp05/ex03
make
./intern
```

O teste solicita os três formulários válidos, assina e executa cada um, depois solicita `coffee request`. As criações válidas devem ser anunciadas; a inválida deve produzir uma mensagem de erro e retornar `0`. A execução também cria `jardim_shrubbery`, que deve conter uma árvore ASCII.

A robotomia pode terminar em sucesso ou falha. A mensagem de formulário desconhecido é escrita em `std::cerr`, então sua posição visual pode variar quando a saída é redirecionada. A confirmação final é:

```text
Todos os testes do ex03 passaram.
```

Para verificar vazamentos, se Valgrind estiver disponível:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./intern
```

O esperado é que não existam blocos definitivamente perdidos. O arquivo `jardim_shrubbery` permanece como resultado da ação do formulário e pode ser inspecionado com `cat`.

## 3. Fluxo do código e decisões de implementação

`Intern` segue a Forma Canônica Ortodoxa, embora não possua atributos. O construtor de cópia e a atribuição recebem o outro objeto para manter a interface exigida, mas não têm estado para copiar.

`makeForm()` define dois arrays paralelos. O primeiro guarda os três nomes aceitos; o segundo guarda ponteiros para funções criadoras com a mesma assinatura. Um único laço procura o nome. Quando encontra, chama a função da mesma posição, imprime a mensagem e retorna o novo objeto.

As funções criadoras ficam no escopo interno de `Intern.cpp` por serem detalhes de implementação. Cada uma converte naturalmente o ponteiro da classe derivada para `AForm*`. A tabela deixa explícita a relação entre nome e classe e evita uma estrutura extensa de `if/else if/else`, rejeitada pelo subject.

Para um nome desconhecido, a busca termina sem alocação. O método usa a mensagem de `UnknownFormException` para explicar o erro e retorna `0`, permitindo que o chamador verifique a falha sem capturar uma exceção. A classe de exceção também documenta esse erro específico sem precisar de Forma Canônica Ortodoxa.

No teste, `useForm()` representa o ciclo completo de propriedade: solicita o formulário, verifica o ponteiro, assina, executa e libera com `delete`. O caso desconhecido confirma que o retorno é nulo; `delete` em um ponteiro nulo é permitido em C++ e não realiza operação alguma.

As classes herdadas do `ex02` preservam o mesmo fluxo: `AForm::execute()` valida assinatura e grau antes de despachar virtualmente `executeAction()`. Dessa forma, o estagiário só escolhe e constrói o tipo; as regras de assinatura e execução continuam sob responsabilidade das classes de formulário.
