# CPP06 — ex02: identificação do tipo real

## 1. O que é o exercício

O exercício define uma classe-base polimórfica `Base` e três classes vazias `A`, `B` e `C`. `generate()` escolhe aleatoriamente uma classe, aloca o objeto e devolve `Base*`. Duas sobrecargas de `identify()` descobrem o tipo real: uma recebe ponteiro e outra recebe referência.

É proibido usar `std::typeinfo` ou incluir `<typeinfo>`. A versão por referência também não pode usar ponteiros. As quatro classes estão dispensadas da Forma Canônica Ortodoxa.

O cast estudado é `dynamic_cast`, que consulta em tempo de execução a hierarquia de um objeto polimórfico.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp06/ex02
make
./identify
```

O programa gera dez objetos. Para cada um, a identificação por ponteiro e por referência deve imprimir a mesma letra. A sequência pode variar, pois a escolha é aleatória. Um ponteiro nulo deve resultar em `Tipo desconhecido`, e a execução termina com:

```text
Todos os testes do ex02 passaram.
```

Cada objeto criado por `generate()` é liberado com `delete`. O destrutor virtual de `Base` garante destruição correta por meio do ponteiro da classe-base.

## 3. Fluxo do código e decisões de implementação

`Base` possui um destrutor virtual público, o que a torna polimórfica e habilita `dynamic_cast`. As classes `A`, `B` e `C` não precisam de atributos nem métodos: seu tipo dinâmico é a informação estudada.

`generate()` inicializa o gerador pseudoaleatório somente na primeira chamada, escolhe 0, 1 ou 2 e retorna uma nova instância como `Base*`.

Na versão por ponteiro, `dynamic_cast<A*>(p)` retorna um ponteiro válido quando o objeto é `A` e `0` quando não é. Por isso, os testes podem ser encadeados diretamente.

Na versão por referência, `dynamic_cast<A&>(p)` retorna a referência quando o tipo corresponde e lança uma exceção quando não corresponde. Como ponteiros são proibidos nessa função e `<typeinfo>` também é proibido, cada tentativa fica em um bloco `try`; `catch (...)` permite seguir para o próximo tipo sem nomear `std::bad_cast`.

O destrutor virtual também é necessário para o `delete object` do teste: o ponteiro tem tipo estático `Base*`, embora o objeto real seja `A`, `B` ou `C`.
