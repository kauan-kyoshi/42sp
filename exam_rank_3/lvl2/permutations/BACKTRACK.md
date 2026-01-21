# Backtracking — Explicação e aplicação no exercício de permutações

Este documento explica o conceito de backtracking (retrocesso), como ele funciona
em termos gerais e como foi utilizado na implementação `permutations_backtrack.c`
do exercício.

## O que é Backtracking?

Backtracking é uma técnica de busca recursiva usada para construir soluções
parciais incrementalmente e descartar (retroceder) caminhos que não levam a
uma solução válida. É especialmente útil quando precisamos explorar um espaço
combinatório (permutations, combinações, N-Queens, sudoku, caminhos em grafos
com restrições, etc.).

Padrão básico:

- Escolher: tente uma opção para a posição atual.
- Rejeitar (prune): se a escolha viola alguma restrição, descarta-a.
- Recursão: avança para a próxima posição com a escolha atual fixa.
- Retroceder: desfaz a escolha e tenta a próxima opção.

Backtracking é, em essência, uma DFS (depth-first search) com restauração do
estado para explorar outras possibilidades.

## Template genérico (em pseudocódigo)

function backtrack(pos):
  if pos == objetivo:
    processa_solucao()
    return
  for cada opção possível na posição pos:
    if opção é válida:
      aplica_opção()
      backtrack(pos + 1)
      desfaz_opção()  // importante: restaura o estado

## Complexidade

Depende do problema. Para permutações de n elementos, sem poda, há n! soluções
e o algoritmo precisa visitar (ou gerar) cada uma, logo o tempo é O(n * n!) se
imprimirmos cada permutação (n para copiar/imprimir cada uma). O uso de poda
e verificações de duplicatas pode reduzir o trabalho quando há repetições.

## Aplicação no exercício: permutações por backtracking

Objetivo: dado uma string de entrada, imprimir todas as permutações únicas
em ordem lexicográfica, uma por linha.

Abordagem adotada em `permutations_backtrack.c`:

1. Copiamos a string de entrada para um buffer mutável e *ordenamos* seus
   caracteres. Ordenar inicialmente é uma técnica simples que facilita gerar
   permutações em ordem lexicográfica quando escolhemos caracteres em ordem.

2. Usamos backtracking **por seleção** (não por troca in-place):
   - Mantemos um buffer `perm` com comprimento `n` onde construiremos a
     permutação atual posição a posição.
   - Mantemos um vetor `used` (tamanho `n`) com 0/1 para indicar quais
     caracteres da string fonte `src` já foram usados na permutação atual.
   - Para preencher `perm[pos]`, iteramos os índices `i` de `0..n-1` e, se
     `used[i] == 0`, usamos `src[i]` como candidato.

3. Evitar permutações duplicadas (quando há caracteres repetidos):
   - Como `src` está ordenado, se encontrarmos `src[i] == src[i-1]` e o
     `src[i-1]` ainda não foi usado (i.e. `used[i-1] == 0`), devemos pular a
     escolha de `src[i]` nesse nível, pois isso geraria permutações que já
     foram (ou serão) cobertas por ter escolhido primeiro `src[i-1]`.
   - A condição implementada é:

       if (i > 0 && src[i] == src[i - 1] && !used[i - 1]) continue;

     Essa verificação garante que, para caracteres repetidos, apenas a primeira
     ocorrência não-usa no mesmo nível será considerada, evitando duplicatas.

4. Quando `pos == n`, `perm` contém uma permutação completa; imprimimos
   usando `puts(perm)`.

5. Após cada chamada recursiva, desfazemos a marcação `used[i] = 0` para permitir
   que o caractere seja usado em outras permutações (retrocesso).

Fluxo resumido (exemplo com `src = "abc"`):

- pos=0: tenta 'a' (marca used[0]=1) -> pos=1
- pos=1: tenta 'b' (marca used[1]=1) -> pos=2
- pos=2: tenta 'c' (marca used[2]=1) -> pos=3 => imprime "abc"
- volta, desfaz used[2], tenta outras opções no pos=2, etc.

Porque a ordenação inicial importa

Se `src` estiver ordenado e iterarmos `i` em ordem crescente, as permutações
serão geradas em ordem lexicográfica porque, em cada nível, escolhemos os
menores caracteres disponíveis primeiro.

## Por que essa versão evita duplicatas corretamente?

Considere caracteres repetidos, p.ex. `a a b` (ordenado). No primeiro nível (pos=0)
há 3 índices, mas escolher a segunda ocorrência de 'a' em vez da primeira
produziria permutações idênticas. A regra `!used[i-1]` assegura que só a
primeira ocorrência livre dos caracteres iguais seja usada primeiro naquele
nível — as demais são puladas até que a anterior seja marcada como usada,
o que garante ordens diferentes e únicas.

## Recursos e limitações

- Memória: usamos O(n) adicional para `perm` e O(n) para `used`.
- Tempo: gera todas as permutações únicas; para todas distintas é O(n * n!).
- Para entradas com n grande (por exemplo n > 10), o número de permutações
  cresce rapidamente; cuidado com tempo de execução e uso de memória se for
  coletar resultados em memória.

## Comandos úteis

Compilar a versão backtrack:

```bash
gcc -Wall -Wextra -O2 -o rendu/permutations/permutations_backtrack \
    rendu/permutations/permutations_backtrack.c
```

Executar com exemplo:

```bash
./rendu/permutations/permutations_backtrack abc
```

Teste com caracteres repetidos:

```bash
./rendu/permutations/permutations_backtrack aab
```

Saída esperada para `aab`:

```
aab
aba
baa
```

## Dicas para 42 (estilo e segurança)

- Prefira evitar armazenamento desnecessário de todas as permutações em memória;
  imprima na hora (como `puts`) para não inflar o uso de memória.
- Verifique sempre retornos de `malloc` e libere memória (`free`) antes de sair.
- Em C, evite recursões muito profundas sem necessidade — para permutações
  recursão é natural e aceitável, mas para n muito grande considere soluções
  iterativas ou limitações de entrada.

## Conclusão

Backtracking fornece um padrão claro e reutilizável para explorar espaços
combinatórios. No exercício de permutações geramos cada permutação por seleção
recursiva, garantindo ordem lexicográfica com uma ordenação inicial e evitando
duplicatas através do teste `!used[i-1]` quando caracteres adjacentes são iguais.

Se quiser, eu posso:

- Adicionar exemplos adicionais, diagramas de recursão, ou uma versão comentada
  passo-a-passo do backtracking para `n=4`.
