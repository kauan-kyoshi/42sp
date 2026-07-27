# CPP04 - Exercise 01

Este exercício implementa herança, polimorfismo, destrutores virtuais e cópia profunda com uma classe auxiliar `Brain`.

## Objetivo

O enunciado pede para:

- criar uma classe base `Animal`;
- criar `Dog` e `Cat` como classes derivadas;
- adicionar uma classe `Brain` com um array de `100` `std::string` chamado `ideas`;
- fazer com que `Dog` e `Cat` possuam um `Brain*` privado;
- garantir que a cópia de `Dog` e `Cat` seja profunda, e não superficial;
- testar o comportamento polimórfico deletando objetos derivados através de ponteiros para `Animal`;
- mostrar que o caso `WrongAnimal` / `WrongCat` não usa polimorfismo corretamente.

## Estrutura das classes

### `Animal`

`Animal` é a classe base da hierarquia.

Responsabilidades:

- guardar o tipo do animal em `std::string type`;
- expor `getType()`;
- declarar `makeSound()` como `virtual` para permitir dispatch dinâmico;
- possuir destrutor `virtual`, para que `delete` via ponteiro para `Animal` chame o destrutor correto.

### `Dog` e `Cat`

`Dog` e `Cat` herdam de `Animal` e representam os casos corretos de polimorfismo.

Cada uma dessas classes:

- define `type` como `"Dog"` ou `"Cat"`;
- sobrescreve `makeSound()`;
- possui um atributo privado `Brain *brain`;
- aloca o `Brain` com `new Brain()` no construtor;
- libera o `Brain` com `delete` no destrutor;
- implementa construtor de cópia e operador de atribuição com cópia profunda.

### `Brain`

`Brain` encapsula as ideias do animal.

Ele contém:

- `std::string ideas[100]`;

Funções principais:

- construtor, construtor de cópia, operador de atribuição e destrutor;
- `setIdea(int, const std::string &)`;
- `getIdea(int) const`.

O papel do `Brain` é permitir testar se `Dog` e `Cat` realmente copiam o conteúdo do objeto apontado, e não apenas o ponteiro.

### `WrongAnimal` e `WrongCat`

Essas classes existem para demonstrar o que acontece quando o polimorfismo não é modelado corretamente.

No caso de `WrongAnimal`:

- `makeSound()` não é `virtual`;
- portanto, ao usar um ponteiro para `WrongAnimal`, a chamada resolve estáticamente para a implementação da classe base.

O resultado é que `WrongCat` não se comporta como uma subclasse polimórfica verdadeira.

## Lógica do programa

O `main.cpp` foi escrito para cobrir vários cenários.

### 1. Array polimórfico de `Animal*`

O programa cria um array de `Animal*`:

- metade dos elementos recebe `new Dog()`;
- a outra metade recebe `new Cat()`.

Depois, o código percorre o array e chama `getType()` e `makeSound()` em cada elemento.

Como `makeSound()` é `virtual`, o método executado é o da classe real do objeto, não o da classe base.

Em seguida, cada elemento é deletado com `delete animals[i];`.

Isso é importante porque o enunciado exige que o delete aconteça através de `Animal*`, e a ordem correta de destruição só funciona porque o destrutor da base é virtual.

### 2. Teste de cópia profunda

O programa cria um `Dog` e um `Cat`, escreve algumas ideias no `Brain` e depois cria cópias desses objetos.

Depois da cópia, o objeto original é alterado.

Se a cópia fosse superficial, a alteração no original apareceria também na cópia, porque ambos apontariam para o mesmo `Brain`.

Como a implementação faz cópia profunda, a cópia mantém o conteúdo anterior, provando que cada objeto possui seu próprio `Brain`.

### 3. Teste de ponteiro para base

O código também faz o teste clássico:

- `const Animal *j = new Dog();`
- `const Animal *i = new Cat();`

Ao chamar `j->makeSound()` e `i->makeSound()`, o resultado correto vem do tipo real dos objetos.

Isso confirma o uso de despacho dinâmico.

### 4. Teste do caso errado

O par `WrongAnimal` / `WrongCat` existe para provar o contraste.

Como `makeSound()` não é `virtual`, a chamada feita por ponteiro para `WrongAnimal` usa a implementação da classe base.

## Conceitos abordados

### Herança

`Dog` e `Cat` reutilizam a interface e parte do comportamento de `Animal`.

### Polimorfismo

Com `virtual`, a chamada do método é resolvida em tempo de execução de acordo com o tipo real do objeto.

### Destrutor virtual

Sem destrutor virtual em `Animal`, deletar um `Dog` ou `Cat` por ponteiro para `Animal` poderia causar comportamento incorreto e vazamento de memória.

### Cópia profunda

Como `Dog` e `Cat` gerenciam memória dinâmica, não basta copiar o ponteiro.

É necessário copiar o conteúdo apontado, garantindo que cada objeto tenha seu próprio `Brain`.

### Regra dos 3

Quando uma classe gerencia recurso dinâmico, normalmente ela precisa de:

- construtor de cópia;
- operador de atribuição;
- destrutor.

`Dog`, `Cat` e `Brain` seguem esse padrão.

## Testes cobertos

O `main.cpp` valida:

- construção e destruição de objetos base e derivados;
- chamadas virtuais por ponteiro para base;
- deleção correta de objetos derivados via `Animal*`;
- cópia profunda de `Dog` e `Cat`;
- comportamento não-polimórfico de `WrongAnimal`.

## Observação

O projeto também foi validado com `valgrind`, e o resultado indicou que não há vazamentos de memória.