# CPP06 — ex01: Serializer

## 1. O que é o exercício

O exercício implementa uma classe não instanciável chamada `Serializer`, com dois métodos estáticos. `serialize(Data*)` converte um ponteiro em `uintptr_t`; `deserialize(uintptr_t)` reconstrói o ponteiro. A estrutura `Data` precisa ser não vazia, portanto contém `id`, `name` e `value`.

O objetivo não é gravar os campos em um arquivo nem produzir uma representação portátil dos dados. Aqui, “serialização” significa preservar numericamente um endereço durante uma ida e volta entre ponteiro e inteiro dentro da mesma execução.

O cast estudado é `reinterpret_cast`, usado em conversões de baixo nível nas quais os bits de um endereço são interpretados como um inteiro capaz de armazená-los, e depois como ponteiro novamente.

## 2. Como testar e o que é esperado

```bash
cd /home/kyoshi/42/42sp/cpp/cpp06/ex01
make
./serializer
```

Os endereços e o inteiro exibidos variam entre execuções e máquinas. O endereço original e o restaurado devem ser iguais, os três campos precisam manter os valores e a última linha deve ser:

```text
Todos os testes do ex01 passaram.
```

Os `assert` interrompem o programa caso o ponteiro ou algum dado não corresponda ao original. O programa não aloca memória dinamicamente, então não existe `new` que precise de `delete`.

## 3. Fluxo do código e decisões de implementação

`Data.hpp` declara uma estrutura com membros reais, atendendo à exigência de que ela não seja vazia. `Serializer.hpp` inclui `<stdint.h>`, que fornece `uintptr_t`: um tipo inteiro sem sinal definido especificamente quando a plataforma oferece uma representação capaz de guardar um ponteiro convertido.

`serialize()` recebe o endereço e aplica `reinterpret_cast<uintptr_t>`. O resultado é passado sem alteração para `deserialize()`, que aplica o cast inverso. A garantia relevante é a ida e volta: o ponteiro reconstruído deve comparar igual ao original.

Os membros canônicos de `Serializer` são privados e não possuem definição, impedindo construção, cópia e atribuição por usuários. Somente os métodos estáticos fazem sentido porque a classe não armazena estado.

O `main()` mantém o objeto `Data` vivo durante toda a conversão. Isso é essencial: converter o endereço não prolonga a vida do objeto. Desreferenciar um endereço depois que o objeto deixa de existir seria inválido.
