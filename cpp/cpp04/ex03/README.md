# CPP04 - Exercise 03

Este exercício fecha o módulo com uma implementação de interfaces em C++98 usando classes abstratas puras.

## Objetivo

O enunciado pede para:

- implementar a classe abstrata `AMateria`;
- criar as matérias concretas `Ice` e `Cure`;
- criar a interface `ICharacter` e a classe concreta `Character`;
- criar a interface `IMateriaSource` e a classe concreta `MateriaSource`;
- garantir cópia profunda de `Character`;
- permitir aprendizado e clonagem de matérias via `MateriaSource`;
- fazer tudo funcionar sem vazamentos de memória.

## O que é uma interface aqui

Em C++98 não existe palavra-chave `interface`, então o padrão usado no exercício é a **classe abstrata pura**.

As interfaces do exercício são:

- `ICharacter`;
- `IMateriaSource`;
- `AMateria` como base abstrata das matérias.

Essas classes expõem apenas o contrato que as classes concretas precisam seguir.

## Estrutura das classes

### `AMateria`

`AMateria` guarda o tipo da matéria em `_type`.

Ela fornece:

- construtor padrão;
- construtor que recebe o tipo;
- construtor de cópia;
- operador de atribuição;
- destrutor virtual;
- `getType()`;
- `clone()` como método puro virtual;
- `use(ICharacter&)`.

O método `clone()` é o ponto central do exercício: ele permite copiar uma matéria sem saber o tipo concreto em tempo de compilação.

### `Ice` e `Cure`

Essas são as matérias concretas.

Elas:

- definem o tipo como `"ice"` e `"cure"`;
- implementam `clone()` retornando uma nova instância do mesmo tipo;
- sobrescrevem `use(ICharacter&)` com a mensagem pedida no enunciado.

### `ICharacter` e `Character`

`ICharacter` define o contrato do personagem:

- `getName()`;
- `equip()`;
- `unequip()`;
- `use()`.

`Character` implementa esse contrato e possui:

- nome;
- inventário com 4 slots;
- uma área interna para guardar matérias descartadas pela `unequip()`;
- construtor com nome;
- construtor de cópia;
- operador de atribuição;
- destrutor.

### `IMateriaSource` e `MateriaSource`

`IMateriaSource` define o contrato da fonte de matérias:

- `learnMateria()`;
- `createMateria()`.

`MateriaSource` armazena até 4 protótipos de matérias e consegue criar novas matérias por tipo usando `clone()`.

## Lógica do programa

O `main.cpp` foi escrito para cobrir o exemplo do enunciado e testes extras.

### 1. Exemplo principal do exercício

O programa cria uma `MateriaSource`, aprende `Ice` e `Cure`, cria um `Character` chamado `me` e equipa matérias criadas por tipo.

Depois cria outro `Character` chamado `bob` e chama:

- `me->use(0, *bob);`
- `me->use(1, *bob);`

Isso gera exatamente o comportamento esperado:

- `* shoots an ice bolt at bob *`
- `* heals bob's wounds *`

### 2. Inventário do Character

O `Character` equipa matérias no primeiro slot vazio, de `0` até `3`.

Se o inventário estiver cheio, a matéria recebida é descartada de forma segura.

Quando `unequip()` é chamado:

- o slot é esvaziado;
- a matéria não é deletada imediatamente;
- o objeto é guardado internamente para ser liberado depois.

Isso respeita o enunciado e evita vazamentos.

### 3. Cópia profunda

Ao copiar um `Character`, as matérias do inventário também são clonadas.

Ou seja:

- o novo `Character` recebe cópias novas;
- os dois personagens não compartilham os mesmos ponteiros de matéria.

Isso é essencial porque `Character` gerencia memória dinâmica.

### 4. MateriaSource

`MateriaSource` aprende matérias como se fossem modelos.

Ao chamar `createMateria("ice")`, por exemplo, ele procura uma matéria aprendida com esse tipo e retorna uma cópia nova.

Se o tipo não existir, retorna `0`.

## Conceitos abordados

### Classe abstrata

`AMateria` não faz sentido como objeto concreto; ela existe para ser especializada.

### Polimorfismo

O código usa ponteiros para interfaces e chamadas virtuais para executar o comportamento correto em tempo de execução.

### Clone virtual

O padrão `clone()` permite copiar objetos sem conhecer o tipo exato em tempo de compilação.

### Cópia profunda

`Character` e `MateriaSource` não podem copiar só os ponteiros.

Eles precisam duplicar os objetos apontados para manter independência e evitar double free ou aliasing indevido.

### Ownership de memória

O exercício exige atenção com quem é dono de cada `AMateria`.

Neste projeto:

- `Character` assume as matérias equipadas;
- matérias descartadas por `unequip()` são armazenadas internamente para serem liberadas depois;
- `MateriaSource` guarda clones dos protótipos aprendidos;
- quando não há espaço, a matéria recebida é descartada com segurança.

## Testes cobertos

O `main.cpp` valida:

- o exemplo principal do enunciado;
- equipar até 4 matérias;
- tentativa de equipar com inventário cheio;
- `use()` em slots válidos e inválidos;
- `unequip()` sem deletar imediatamente a matéria;
- cópia construtiva e por atribuição de `Character`;
- criação de matérias desconhecidas retornando `0`.

## Resumo

Este exercício resume os pontos mais importantes do módulo:

- classes abstratas como interfaces;
- herança e polimorfismo;
- cópia profunda com recursos dinâmicos;
- gerenciamento correto de memória;
- uso de `clone()` como padrão de criação polimórfica.