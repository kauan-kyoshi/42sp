# cpp02 - ex01

## O que este exercício faz

Este exercício evolui a classe `Fixed` para representar números em ponto fixo de verdade.

Agora a classe aceita:

- `int`
- `float`

Ela também consegue converter o valor interno de volta para `float` com `toFloat()` e para `int` com `toInt()`.

## Como funciona

O número fixo usa 8 bits fracionários.

- Quando recebe um `int`, o valor é deslocado 8 bits para a esquerda.
- Quando recebe um `float`, o valor é multiplicado por $2^8$ e arredondado.
- `toFloat()` divide o valor bruto por $2^8$.
- `toInt()` remove a parte fracionária deslocando 8 bits para a direita.
- `operator<<` permite imprimir o objeto diretamente em `std::cout`.

## Fluxo de trabalho

1. O `main()` cria um objeto padrão para demonstrar o valor zero inicial.
2. Depois cria um `Fixed` a partir de `int` e outro a partir de `float`.
3. Um quarto objeto é inicializado por cópia para validar o construtor de cópia.
4. O programa faz uma atribuição com um temporário para testar a conversão e a troca de estado.
5. Os objetos são impressos com `operator<<` e também convertidos com `toInt()` para comparar as representações.
6. Ao final, os objetos são destruídos automaticamente.

## Lógica do código

Aqui a classe passa a representar um número em ponto fixo com 8 bits fracionários.

- O valor interno `_rawBits` armazena o número escalado por $2^8$.
- O construtor com `int` desloca o valor bruto porque um inteiro não tem parte fracionária.
- O construtor com `float` usa `roundf()` para preservar a melhor aproximação possível antes de guardar o valor.
- `toFloat()` desfaz a escala para recuperar um número legível.
- `toInt()` descarta a parte fracionária, então o resultado é uma aproximação inteira do valor armazenado.
- O operador de saída usa `toFloat()` porque essa é a forma mais útil de visualizar o conteúdo do objeto.

O `main.cpp` demonstra:

- construção padrão
- construção com `int`
- construção com `float`
- construtor de cópia
- atribuição com objeto temporário
- impressão como `float`
- conversão para `int`

## Como testar

Dentro da pasta `ex01`:

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

- Representação em ponto fixo
- Deslocamento de bits
- Conversão entre `int` e `float`
- Arredondamento com `roundf`
- Sobrecarga do operador de saída `<<`
- Construtores sobrecarregados
- Encapsulamento de dados

## O que observar na execução

O valor mostrado ao imprimir o objeto deve refletir o número original com aproximação de ponto fixo. O `toInt()` deve mostrar apenas a parte inteira.