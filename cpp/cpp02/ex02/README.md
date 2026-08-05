# cpp02 - ex02

## O que este exercício faz

Este exercício completa a classe `Fixed` com as operações esperadas para um tipo numérico:

- comparação
- soma, subtração, multiplicação e divisão
- incremento e decremento pré e pós
- `min` e `max`

A classe passa a se comportar como um tipo numérico em ponto fixo mais completo.

## Como funciona

- Os operadores de comparação (`>`, `<`, `>=`, `<=`, `==`, `!=`) comparam o valor bruto `_rawBits`.
- `operator+` e `operator-` trabalham diretamente no valor interno.
- `operator*` multiplica usando `long long` para reduzir risco de overflow e depois ajusta o resultado pelos bits fracionários.
- `operator/` também usa `long long` para preservar precisão; se o divisor for zero, retorna `0` em ponto fixo.
- `operator++` e `operator--` alteram o valor unitariamente em ponto fixo.
- As versões pós-fixadas retornam uma cópia do valor antigo.
- `min` e `max` retornam referência para o menor ou maior valor, tanto em versão mutável quanto `const`.
- O construtor privado `Fixed(int rawBits, bool)` é usado para criar objetos a partir do valor bruto sem aplicar conversão novamente.

## Fluxo de trabalho

1. O `main()` cria um objeto padrão para iniciar em zero.
2. Em seguida, cria uma expressão com multiplicação para testar a operação aritmética principal do exercício.
3. O programa imprime o valor inicial, depois aplica incremento pré-fixado e imprime novamente.
4. Depois usa incremento pós-fixado para mostrar a diferença entre retornar o valor antigo e atualizar o objeto.
5. Por fim, chama `Fixed::max(a, b)` para validar a comparação e a função auxiliar estática.

## Lógica do código

Esta etapa transforma `Fixed` em um tipo numérico completo em ponto fixo.

- As comparações usam o valor bruto porque ele representa diretamente a ordem numérica real.
- A soma e a subtração podem operar no inteiro interno sem reescalar.
- A multiplicação precisa corrigir a escala depois do produto, por isso usa deslocamento à direita após multiplicar.
- A divisão precisa reescalar o numerador antes de dividir, mantendo a precisão do resultado.
- Os operadores de incremento e decremento alteram o menor incremento possível na representação fixa, ou seja, um passo de 1 unidade no valor bruto.
- `min` e `max` só escolhem qual referência retornar, sem criar cópias desnecessárias.
- O construtor privado com `bool` é um atalho interno para montar objetos já escalados, sem repetir conversão.

O `main.cpp` mostra:

- criação de valores fixos
- multiplicação entre `Fixed(5.05f)` e `Fixed(2)`
- incremento pré e pós
- uso de `Fixed::max(a, b)`

## Como testar

Dentro da pasta `ex02`:

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

- Sobrecarga de operadores
- Operadores aritméticos em classes
- Operadores de comparação
- Incremento e decremento pré/pós-fixado
- Funções utilitárias estáticas
- Manipulação de precisão em ponto fixo
- Uso de `const` para segurança de interface

## O que observar na execução

Você deve ver os valores antes e depois dos incrementos, além do resultado da multiplicação e do `max`. Isso confirma que a classe está se comportando como um tipo numérico completo.