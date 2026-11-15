# CPP05 — ex02: formulários abstratos

## 1. O que é o exercício

O exercício transforma `Form` em `AForm`, uma classe abstrata, e introduz três formulários concretos. `ShrubberyCreationForm` exige graus 145 para assinatura e 137 para execução, cria `<target>_shrubbery` e escreve uma árvore ASCII. `RobotomyRequestForm` exige 72 e 45, produz ruídos e informa sucesso ou falha com probabilidade de 50%. `PresidentialPardonForm` exige 25 e 5 e informa que o alvo foi perdoado por Zaphod Beeblebrox.

Todos recebem somente o alvo em seu construtor. `AForm::execute()` deve impedir a ação quando o formulário não estiver assinado ou quando o executor tiver grau insuficiente. `Bureaucrat::executeForm()` tenta executar e imprime sucesso ou uma causa explícita de falha.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp05/ex02
make
./abstract_forms
```

O teste primeiro tenta executar um formulário não assinado, rejeita a assinatura de um burocrata de grau 150 e depois executa os três formulários com um burocrata de grau 1. Também testa a recusa de execução da robotomia por grau insuficiente.

Deve ser criado `casa_shrubbery` no diretório de execução, contendo uma árvore ASCII. A robotomia pode informar sucesso ou falha; ambos são resultados válidos. A última linha deve ser:

```text
Todos os testes do ex02 passaram.
```

Para inspecionar e limpar o arquivo gerado:

```bash
cat casa_shrubbery
rm casa_shrubbery
```

Também estão disponíveis `make clean`, `make fclean` e `make re`.

## 3. Fluxo do código e decisões de implementação

`AForm` mantém privados o nome, o estado de assinatura e os dois graus. Sua função protegida `executeAction()` é virtual pura, tornando a classe abstrata. O destrutor é virtual para permitir destruir corretamente um formulário concreto por um ponteiro `AForm*`.

O fluxo de execução usa o padrão Template Method: `AForm::execute()` verifica primeiro se o formulário está assinado e depois o grau do executor. Somente após as duas validações chama `executeAction()`. As subclasses implementam a ação específica sem repetir as regras comuns.

`ShrubberyCreationForm` abre o arquivo com `std::ofstream`, usando `c_str()` por compatibilidade com C++98. A abertura e a escrita são verificadas; uma falha lança `FileCreationException`. `RobotomyRequestForm` usa `std::rand() % 2`, que seleciona dois resultados possíveis de forma equilibrada. `PresidentialPardonForm` apenas imprime sua mensagem.

Cada classe concreta segue a Forma Canônica Ortodoxa. O alvo é constante e identifica a instância; em uma atribuição, a parte `AForm` copia o estado de assinatura, enquanto nome, requisitos e alvo do destino permanecem inalterados.

`Bureaucrat::executeForm()` captura as exceções da interface-base. Assim, o mesmo código funciona para qualquer implementação de `AForm`. O `main.cpp` cobre a ordem das validações, graus insuficientes, as três ações e os requisitos fixos de cada classe.
