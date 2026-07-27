# CPP04 - Exercise 02

Este exercício transforma a classe `Animal` em uma classe abstrata e mantém o restante da hierarquia funcionando como antes.

## Objetivo

O enunciado pede para:

- impedir a instanciação direta de `Animal`;
- manter `Dog` e `Cat` funcionando normalmente;
- preservar o polimorfismo por ponteiros para a classe base;
- continuar com o teste de cópia profunda usando `Brain`;
- manter o exemplo de `WrongAnimal` / `WrongCat` para mostrar o caso incorreto.

## O que mudou em relação ao exercício anterior

A principal mudança está em `Animal`:

- `makeSound()` virou método puro virtual;
- por isso, `Animal` não pode mais ser instanciada.

Na prática, isso comunica ao compilador que `Animal` existe apenas como interface/base para outras classes, e não como um objeto concreto.

## Estrutura das classes

### `Animal`

`Animal` continua armazenando o atributo protegido `std::string type`.

Ela ainda possui:

- `getType()`;
- construtor, construtor de cópia, operador de atribuição e destrutor com mensagens próprias;
- destrutor virtual, para garantir destruição correta via ponteiro para a base.

Agora, porém, `makeSound()` é declarado como:

- `virtual void makeSound() const = 0;`

Isso a torna abstrata.

### `Dog` e `Cat`

`Dog` e `Cat` continuam sendo as classes concretas da hierarquia.

Cada uma delas:

- define seu `type` como `"Dog"` ou `"Cat"`;
- sobrescreve `makeSound()`;
- mantém o ponteiro privado `Brain *brain`;
- aloca o `Brain` no construtor;
- libera o `Brain` no destrutor;
- implementa cópia profunda no construtor de cópia e no operador de atribuição.

### `Brain`

`Brain` continua representando o estado interno do animal.

Ele contém:

- um array `std::string ideas[100]`;

e fornece:

- `setIdea()`;
- `getIdea()`;
- construtor, cópia, atribuição e destrutor.

### `WrongAnimal` e `WrongCat`

Essas classes continuam no projeto como contraste didático.

Elas mostram o que acontece quando o método da base não é `virtual`.

## Lógica do programa

O `main.cpp` foi mantido com testes mais completos.

### 1. Array polimórfico

O programa cria um array de `Animal *` e preenche:

- metade com `new Dog()`;
- metade com `new Cat()`.

Depois percorre o array chamando `getType()` e `makeSound()`.

Esse teste confirma que o dispatch dinâmico continua funcionando com `Animal` abstrata.

### 2. Destruição via ponteiro para a base

Os elementos do array são deletados com `delete` usando o tipo `Animal *`.

Isso garante que os destrutores das classes derivadas sejam chamados corretamente.

### 3. Cópia profunda

O programa altera ideias dentro do `Brain` de um `Dog` e de um `Cat`, cria cópias e depois modifica os objetos originais.

Se a cópia fosse rasa, as alterações apareceriam nas cópias também.

Como a implementação é profunda, os valores permanecem independentes.

### 4. `WrongAnimal` / `WrongCat`

O teste final mostra que, sem `virtual`, uma chamada por ponteiro para a base usa a implementação da classe base, e não a derivada.

## Conceitos abordados

### Classe abstrata

Uma classe abstrata não pode ser instanciada diretamente.

Ela serve como contrato base para outras classes.

### Método puro virtual

`makeSound()` em `Animal` é declarado como puro virtual para forçar as classes derivadas a fornecerem sua própria implementação.

### Polimorfismo

Ao chamar métodos em ponteiros para `Animal`, o comportamento real depende do tipo do objeto.

### Destrutor virtual

É necessário para liberar corretamente objetos derivados quando o ponteiro é da classe base.

### Regra dos 3

Como `Dog` e `Cat` gerenciam memória dinâmica com `Brain *`, elas precisam de:

- construtor de cópia;
- operador de atribuição;
- destrutor.

### Cópia profunda

Cada animal precisa ter seu próprio `Brain`.

Copiar só o ponteiro geraria compartilhamento indevido de estado e possíveis problemas de memória.

## Testes cobertos

O `main.cpp` cobre:

- criação de vários `Dog` e `Cat` por ponteiro para `Animal`;
- chamadas de `getType()`;
- chamadas polimórficas de `makeSound()`;
- destruição correta dos objetos;
- cópia profunda de `Dog` e `Cat`;
- comparação com `WrongAnimal` / `WrongCat`.

## Resumo

Este exercício fecha a evolução da hierarquia:

- no `ex00`, o polimorfismo é introduzido;
- no `ex01`, a memória dinâmica entra com `Brain`;
- no `ex02`, `Animal` vira abstrata para evitar instâncias sem sentido.

O resultado é uma hierarquia mais correta e segura para representar animais concretos.