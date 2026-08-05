# cpp02 - ex00

## O que este exercício faz

Este primeiro exercício cria a base da classe `Fixed`. A ideia é representar um número em ponto fixo usando um `int` interno chamado `_rawBits`.

Nesta etapa a classe ainda não converte valores reais: ela só mostra o ciclo de vida do objeto e expõe acesso ao valor bruto com `getRawBits()` e `setRawBits()`.

## Como funciona

- O construtor padrão inicializa `_rawBits` com `0`.
- O construtor de cópia cria um novo objeto a partir de outro `Fixed`.
- O operador de atribuição copia o valor bruto do objeto de origem.
- O destrutor apenas informa quando o objeto está sendo destruído.
- `getRawBits()` retorna o valor inteiro interno e também imprime uma mensagem de teste.

## Fluxo de trabalho

1. O programa entra em `main()` e cria um objeto `Fixed` padrão.
2. Em seguida, cria um segundo objeto usando o construtor de cópia.
3. Depois cria um terceiro objeto padrão e recebe o valor do segundo por atribuição.
4. Por fim, chama `getRawBits()` nos três objetos para mostrar os valores internos.
5. Ao sair de escopo, os destrutores são chamados automaticamente na ordem inversa de criação.

## Lógica do código

Neste exercício o foco não é fazer cálculos ainda, mas validar a estrutura básica da classe.

- `_rawBits` guarda o estado real do objeto.
- O construtor de cópia e o operador de atribuição garantem que esse estado seja duplicado corretamente.
- O método `getRawBits()` serve para inspecionar o valor interno e confirmar que a cópia e a atribuição funcionam.
- A mensagem impressa em cada método existe para mostrar a ordem exata de execução durante o teste.

O `main.cpp` cria três objetos para demonstrar:

- construção padrão
- construção por cópia
- atribuição entre objetos
- leitura do valor bruto

## Como testar

Dentro da pasta `ex00`:

```bash
make
./fixed
```

Para limpar:

```bash
make clean
make fclean
```

## Conceitos abordados

- Classe em C++
- Encapsulamento
- Construtor padrão
- Construtor de cópia
- Operador de atribuição
- Destrutor
- `const` em métodos
- Introdução ao conceito de ponto fixo

## O que observar na execução

Você deve ver mensagens indicando quando cada construtor, método e destrutor é chamado. Isso ajuda a entender a ordem de execução dos objetos em C++.