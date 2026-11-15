# CPP05 — ex01: Form

## 1. O que é o exercício

O exercício amplia o `ex00` com a classe `Form`. Um formulário possui nome constante, estado de assinatura, grau constante necessário para assinar e grau constante necessário para executar. Todos os atributos são privados. Os graus seguem o mesmo intervalo do burocrata: de 1, o mais alto, até 150, o mais baixo.

O construtor rejeita qualquer requisito fora desse intervalo com `Form::GradeTooHighException` ou `Form::GradeTooLowException`. `beSigned()` recebe um `Bureaucrat` e assina o formulário quando o grau do burocrata é numericamente menor ou igual ao requisito. Um burocrata de grau 50 pode assinar um formulário que exige 50; um de grau 51 não pode.

`Bureaucrat::signForm()` concentra a interação para quem usa as classes: chama `beSigned()`, captura uma possível exceção e informa se o burocrata conseguiu assinar. O exercício também exige getters e `operator<<` com todas as informações do formulário.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp05/ex01
make
./forms
```

A compilação deve passar com `-Wall -Wextra -Werror -std=c++98`. A saída esperada inclui uma falha do burocrata de grau 51, sucessos dos graus 50 e 1, os dados do formulário e a confirmação final:

```text
Júnior não conseguiu assinar Licença porque classificação do burocrata baixa demais.
Exato assinou Licença
Chefe assinou Licença
Licença, assinado: sim, grau para assinar: 50, grau para executar: 20.
Todos os testes do ex01 passaram.
```

Os `assert` verificam silenciosamente graus inválidos, o limite exato para assinatura, a Forma Canônica Ortodoxa e a saída do formulário. Também podem ser usados `make clean`, `make fclean` e `make re`.

## 3. Fluxo do código e decisões de implementação

`Form.hpp` usa uma declaração antecipada de `Bureaucrat`, pois a interface precisa apenas receber uma referência. `Form.cpp` inclui o cabeçalho completo para chamar `getGrade()`. `Bureaucrat` faz o mesmo no sentido inverso, evitando dependência circular entre os cabeçalhos.

Na construção, os quatro membros de `Form` são inicializados pela lista de inicialização. Os requisitos são conferidos antes que a construção termine. Assim, todo formulário existente possui graus válidos e começa não assinado.

Ao chamar `beSigned()`, o código compara o grau do burocrata com `gradeToSign`. Como números menores representam graus mais altos, somente `bureaucrat.getGrade() > gradeToSign` é uma falha. A alteração para `true` acontece depois da validação, preservando o estado em caso de exceção.

`signForm()` chama essa operação dentro de `try`. No sucesso, imprime a confirmação. Na falha, captura por `const std::exception &`, usa o método virtual `what()` e mantém a exceção contida nessa função, como pede o subject.

O construtor de cópia replica todos os membros. Na atribuição, nome e requisitos permanecem os do objeto de destino porque são constantes; somente o estado de assinatura pode ser copiado. Isso mantém a identidade e as regras originais do formulário já construído.

`operator<<` usa apenas getters públicos, portanto não precisa de `friend`. Ele retorna o fluxo para permitir encadeamento. O `main.cpp` separa os testes em criação inválida, assinatura e comportamento canônico, incluindo um teste em que o grau é exatamente o exigido.
