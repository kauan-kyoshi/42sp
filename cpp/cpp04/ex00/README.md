# CPP04 - Exercise 00

Este exercício introduz polimorfismo em C++ com uma hierarquia simples de classes.

## Objetivo

O enunciado pede para:

- criar uma classe base `Animal`;
- criar `Dog` e `Cat` como classes derivadas;
- fazer com que cada classe tenha um construtor e um destrutor com mensagens próprias;
- implementar `makeSound()` para cada tipo de animal;
- mostrar o comportamento correto de despacho dinâmico ao chamar métodos por ponteiros para a classe base;
- criar também o caso `WrongAnimal` / `WrongCat` para mostrar o que acontece quando o método não é `virtual`.

## Estrutura das classes

### `Animal`

`Animal` é a classe base da hierarquia.

Ela contém:

- o atributo protegido `std::string type`;
- `getType()` para ler o tipo;
- `makeSound()` como método `virtual`;
- destrutor `virtual`, para permitir destruição correta via ponteiro para a base.

### `Dog` e `Cat`

`Dog` e `Cat` herdam de `Animal`.

Cada uma dessas classes:

- define o valor de `type` como `"Dog"` ou `"Cat"`;
- sobrescreve `makeSound()`;
- possui construtor, construtor de cópia, operador de atribuição e destrutor com mensagens específicas.

### `WrongAnimal` e `WrongCat`

Essas classes existem para demonstrar o comportamento errado.

No caso de `WrongAnimal`:

- `makeSound()` não é `virtual`.

Por isso, quando um `WrongCat` é acessado por ponteiro para `WrongAnimal`, a chamada não resolve para o tipo real do objeto, mas para a implementação da classe base.

## Lógica do programa

O `main.cpp` foi escrito para testar vários cenários.

### 1. Polimorfismo com ponteiros para `Animal`

O programa cria objetos desta forma:

- `const Animal *meta = new Animal();`
- `const Animal *j = new Dog();`
- `const Animal *i = new Cat();`

Depois chama:

- `getType()`;
- `makeSound()`.

O ponto principal aqui é que `makeSound()` é `virtual`, então o método executado depende do tipo real do objeto.

### 2. Destruição correta

Os objetos são apagados com `delete` através de ponteiros para `Animal`.

Isso é importante porque o destrutor da base precisa ser `virtual` para que o destrutor da classe derivada também seja chamado.

### 3. Teste com `WrongAnimal`

O teste com `WrongAnimal` e `WrongCat` mostra que, sem `virtual`, o polimorfismo não funciona como esperado.

Isso ajuda a entender por que o uso de `virtual` é essencial nesse tipo de hierarquia.

## Conceitos abordados

### Herança

`Dog` e `Cat` reaproveitam a estrutura e a interface de `Animal`.

### Polimorfismo

Métodos `virtual` permitem que a chamada seja resolvida em tempo de execução.

### Destrutor virtual

Sem destrutor virtual, deletar um objeto derivado por ponteiro da classe base pode causar comportamento incorreto.

### Sobrescrita de método

Cada classe derivada fornece sua própria versão de `makeSound()`.

### Diferença entre correção e erro de modelagem

O par `WrongAnimal` / `WrongCat` serve para mostrar o que acontece quando a classe base não foi modelada com `virtual`.

## Testes cobertos

O `main.cpp` testa:

- construção de `Animal`, `Dog` e `Cat`;
- chamadas de `getType()`;
- dispatch dinâmico de `makeSound()`;
- destruição via ponteiro para a base;
- comportamento errado de `WrongAnimal` / `WrongCat`.

## Resumo

Este exercício é a base para entender:

- herança;
- polimorfismo em C++;
- a importância de métodos e destrutores virtuais;
- como diferenciar uma hierarquia bem modelada de uma hierarquia com comportamento incorreto.