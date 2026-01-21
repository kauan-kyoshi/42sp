# Backtracking aplicado ao problema das N Rainhas

Este documento explica o conceito de *backtracking* (retrocesso), como ele funciona em termos gerais

## 1. O que é Backtracking?

Backtracking é uma técnica de busca recursiva usada para construir soluções
parciais e explorar um espaço de possibilidades. A ideia é:

- Tentar uma escolha para a posição atual.
- Avançar recursivamente (DFS) para preencher a próxima posição.
- Se a escolha levar a uma inconsistência ou não resultar numa solução,
  desfazemos a escolha (retrocedemos) e tentamos a próxima opção.

É uma forma de pesquisa exaustiva com restauração de estado; é útil quando
precisamos enumerar (ou encontrar) todas as soluções de um problema
combinatório sujeito a restrições.

## 2. Template genérico

Em pseudocódigo:

function backtrack(pos):
  if pos == objetivo:
    processa_solucao()
    return
  for cada opção disponível:
    if opção válida:
      aplica_opção()
      backtrack(pos + 1)
      desfaz_opção()

## 3. Como o backtracking é usado no problema das N rainhas

Problema: colocar n rainhas num tabuleiro n x n de forma que nenhuma ataque
outra (mesma linha, mesma coluna ou mesma diagonal). Neste exercício imprimimos
todas as soluções possíveis, cada solução sendo uma sequência `p0 p1 ... p{n-1}`
onde `pi` é a linha da rainha na coluna `i`.

Estratégia usada no código `n_queens.c`:

- Representação: um vetor `cols` de tamanho `n` onde `cols[j]` é a linha da
  rainha na coluna `j` (colunas preenchidas da esquerda para a direita).
- Recursão por colunas: a função recursiva `solve_rec(cols, col, n)` tenta
  colocar uma rainha na coluna `col`. Se `col == n`, uma solução completa foi
  encontrada e é impressa.
- Validação local: antes de colocar uma rainha em `(col,row)`, chamamos
  `is_safe(cols, col, row)` que verifica conflitos com todas as colunas j < col:
  - mesma linha? (cols[j] == row)
  - mesma diagonal? (|cols[j] - row| == col - j)

Fluxo típico (exemplo, n=4):

- Coluna 0: tenta linhas 0..3; digamos que coloca em linha 1 (cols[0]=1).
- Coluna 1: tenta linhas 0..3, pula as que conflitam com cols[0]. Se encontra
  uma, coloca e recursa para coluna 2.
- Quando `col == n` a solução é impressa: `1 3 0 2` etc.

## 4. Evitar estados inválidos cedo (poda)

O `is_safe` realiza a poda local: antes de aprofundar no espaço de busca,
verificamos se a escolha atual viola as restrições. Isso evita explorar ramos
completamente inválidos, reduzindo drasticamente o número de nós visitados.

## 5. Complexidade e memória

- Complexidade no pior caso: tempo proporcional ao número de permutações
  compatíveis, que é O(n * n!) se imprimirmos todas (n para escrever cada
  permutação). Para n grandes o custo cresce muito rápido.
- Memória: O(n) adicional para o vetor `cols` e profundidade máxima de recursão
  de n (pilha de recursão). Não armazenamos todas as soluções em memória —
  imprimimos à medida que as encontramos.

## 6. Por que essa abordagem é adequada para o exercício

- Usa apenas operações permitidas (no código usamos `atoi`, `malloc`, `free`
  e `write` para saída).
- Gera todas as soluções e imprime no formato exigido sem armazenar tudo em
  memória (bom para limites de memória em ambientes de avaliação).
- A verificação `is_safe` garante poda eficiente e mantém o código simples.

## 7. Comandos úteis

Compilar localmente com flags estritas (recomendado para 42):

```bash
gcc -Wall -Werror -Wextra -O2 -o rendu/n_queens/n_queens \
    rendu/n_queens/n_queens.c
```

Executar exemplos:

```bash
./rendu/n_queens/n_queens 4   # deve imprimir duas linhas (1 3 0 2 e 2 0 3 1)
./rendu/n_queens/n_queens 8   # deve imprimir 92 soluções
```

## 8. Dicas para 42

- Garanta que o código compila com `-Wall -Werror -Wextra` (verificações de
  retorno de `write` foram adicionadas por esse motivo).
- Sempre verifique retornos de `malloc` e libere memória antes de sair.
- Para debugging, teste n pequenos (2..8) e verifique números de soluções
  conhecidos (ex.: n=8 tem 92 soluções).

---