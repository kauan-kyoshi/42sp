## push_swap — Guia completo para passar na avaliação da 42

Este repositório contém a solução do projeto "push_swap" da 42. Este documento explica detalhadamente o objetivo do projeto, as restrições, as operações permitidas, os critérios de avaliação e todas as recomendações práticas (estratégias, testes e verificações) para que você passe na avaliação.

Siga este guia como check-list antes de submeter ao avaliador.

## 1 — Objetivo do projeto

O objetivo do projeto é escrever um programa `push_swap` que recebe uma lista de números inteiros distintos e imprime uma sequência de operações que, quando aplicadas a uma pilha A (inicializada com os números na ordem dada), resultam em A ordenada em ordem crescente. Você também deve fornecer um programa `checker` (opcionalmente) que lê a lista inicial e a sequência de operações e verifica se o resultado é ordenado.

O avaliador testa tanto corretude (a sequência realmente ordena) quanto eficiência (número de operações), além de conformidade com as regras da 42 (Norminette, uso restrito de funções, gerenciamento de memória, etc.).

## 2 — Regras e restrições

- Entrada: argumentos passados pela linha de comando (pode haver uma string com vários números ou múltiplos argumentos). Cada token representa um inteiro com sinal.
- Números devem ser validados: formato correto, sem overflow (valor dentro do intervalo de int), e sem duplicatas.
- Operações permitidas (somente estas podem ser impressas):
  - sa, sb, ss
  - pa, pb
  - ra, rb, rr
  - rra, rrb, rrr
- Não pode usar funções de ordenação prontas (qsort, etc.).
- Deve cuidar de leaks de memória (valgrind no teste local é recomendado).

## 3 — Critérios de avaliação (o que o avaliador olha)

- Correção: o algoritmo ordena corretamente todas as entradas válidas.
- Robustez: parsing correto, mensagens de erro (ou encerramento apropriado) para entradas inválidas.
- Número de operações: para entradas pequenas (2..5) deve ser ótimo ou quase ótimo; para entradas maiores espera-se uma estratégia que seja razoavelmente eficiente (radix, chunking, etc.).
- Qualidade do código: estilo (Norminette), organização, funções bem nomeadas, ausência de warnings (compilador com -Wall -Wextra -Werror).
- Memória: sem leaks, sem acessos inválidos.

## 4 — Como o projeto é tradicionalmente avaliado (pontos práticos)

- 2 elementos: até 1 operação (sa) quando necessário.
- 3 elementos: até 2-3 operações (uma solução ótima é conhecida e simples).
- 4 e 5 elementos: geralmente exige estratégia específica (mover menores para B, ordenar 3 em A, depois pa).
- >5 elementos: estratégias comuns:
  - Radix (indexado) — robusto e simples, bom para 500 elementos.
  - Chunking (dividir em blocos por índices) — pode reduzir o número de operações quando bem ajustado.

Obs: o avaliador da 42 pode ter testes com limites como 100 e 500 elementos; muitas soluções têm metas para esses tamanhos.

## 5 — Estrutura do repositório e arquivos importantes

- `Makefile` — regras para compilar `push_swap` e `checker`.
- `includes/push_swap.h` — protótipos, structs e helpers públicos (totalmente documentado com comentários).
- `src/*.c` — implementação:
  - `main.c` / `parse_*` — parsing e validação de argumentos
  - `ops_*.c` — implementações das operações (sa, pb, ra, rra, ...)
  - `sort_small.c` — algoritmos ótimos para 2 e 3
  - `small_cases.c` — **[REFATORADO - NOV/2025]** trata casos especiais (4 e 5 elementos) com estratégia de mover menores para B
  - `sort_many.c` — algoritmo para muitos elementos (chunking com blocos 5/11)
  - `sort_router.c` — escolhe qual rotina chamar de acordo com o tamanho
  - `pull_b.c` — **[REFATORADO - NOV/2025]** segunda fase: reinsere elementos de B para A (do maior para o menor)
  - `utils_*.c` — helpers (get_value, find_min_value, is_sorted, distance_to_top, etc.)
  - `checker.c` / `checker_ops.c` — programa `checker` local com contagem de operações
- `libft/` — biblioteca auxiliar (dlist, ft_printf, ft_split, etc.).

## 6 — Requisitos de parsing e validação (detalhado)

1. Aceitar tanto argumentos separados quanto uma string com vários números. Exemplo válido:

   ./push_swap "2 1 3"   # ou ./push_swap 2 1 3

2. Ignorar espaços extras e controlar sinais.

3. Verificar overflow: use `long` ao converter (ou `ft_atol`) e rejeite se fora do intervalo de `int`.

4. Rejeitar entradas não-numéricas: `./push_swap 1 2 a` -> erro.

5. Rejeitar duplicatas — antes de indexar/ordenar, verifique duplicatas.

6. Em caso de erro: imprimir `Error` na saída padrão de erro e terminar com código != 0 (seguindo a norma da 42 costuma ser `write(2, "Error\n", 6)` e `exit(1)`).

## 7 — Representação interna recomendada

- Pilhas A e B como listas duplamente ligadas (dlist) ou arrays com rotação lógica. Este projeto usa `t_dlist` e `t_dnode` na `libft`.
- Cada nó guarda o valor original e, opcionalmente, o índice (posição na ordem ordenada). O índice é útil para radian sort e chunking.

## 8 — Estratégias por tamanho

8.1 Casos triviais (2, 3)

- `sort_2`: se primeiro > segundo -> `sa`.
- `sort_3`: analisar 3 valores e aplicar até 2 operações (sa/ra/rra) — existem 5 casos.

8.2 Casos de 4 e 5 (detalhado — bastante importante para a avaliação)

- Estratégia clássica para 4:
  1. Encontre a posição do menor elemento.
  2. Rote ele para o topo com `ra`/`rra` (menor número entre rotações).
  3. `pb` (envia para B).
  4. `sort_3` em A.
  5. `pa` (volta o menor).

- Estratégia clássica para 5:
  1. Repetir o processo de mover o menor para B duas vezes (colocar os dois menores em B).
  2. `sort_3` em A.
  3. `pa` duas vezes (retornando do menor para o topo). Se necessário, ajustar com `sa`.

Essas estratégias costumam ser aceitas como corretas e eficientes para a avaliação. Verifique sempre se você está empurrando os menores — por isso indexar a pilha (0..n-1) ajuda.

8.3 Muitos elementos — duas abordagens comprovadas

- Radix por índice (base 2):
  - Indexe os valores de 0..n-1 (menor recebe 0, maior n-1).
  - Para cada bit (0..max_bits): percorra A, envie `pb` se o bit em questão for 0, caso contrário `ra`.
  - Ao fim de cada bit, `pa` até B ficar vazia. Complexidade O(n * max_bits).
  - Simples de implementar e com comportamento estável até n=500 com contagem aceitável de operações.

- Chunking / divisão por blocos:
  - Divida a sequência indexada em blocos (chunks). Por exemplo, para n=100 pode usar 5 a 8 chunks.
  - Percorra A e envie para B os elementos cujo índice pertence ao bloco atual, movendo-os de forma a minimizar rotações.
  - Ao puxar de B para A, sempre traga o maior disponível para o topo (para montar a pilha final ordenada). Usa `rb`/`rrb` para posicionar.
  - Requer mais ajuste fino (tamanho dos chunks, heurísticas) mas tende a produzir menos operações se bem feito.

## 9 — Dicas de otimização (reduzir número de operações)

- Sempre indexe os números: trabalhar com índices torna comparações e decisões de chunk/radix triviais.
- Para mover um elemento a partir de posição p ao topo, escolha entre `ra` p vezes ou `rra` (size-p) vezes—escolha o menor custo.
- Ao empurrar elementos para B durante chunking, tente posicionar os elementos de B para que o melhor candidato seja fácil de puxar (usar `rb` logo após `pb` quando faz sentido).
- Evite operações desnecessárias (`ra` seguido por `rra` é redundante). Após gerar a sequência, pode-se tentar um pass de otimização que elimina pares inversos (e.g., `ra` + `rra`).

## 10 — Implementação das operações (conselhos práticos)

- Cada operação deve atualizar corretamente `head`, `tail`, `size` de cada lista.
- `sa/sb`: trocar os dois primeiros nodes se existirem pelo menos 2.
- `pa/pb`: copiar o valor do topo da pilha fonte para destino — cuide de alocação e desalocação (neste projeto, a libft parece usar duplicação de int e gerenciamento via `free_int`).
- `ra/rb/rr`: mover head para tail (rotacionar para cima).
- `rra/rrb/rrr`: mover tail para head (rotacionar para baixo).

Imprima as operações exatamente como strings com newline (e.g., `write(1, "ra\n", 3)`).

## 11 — Funções refatoradas e documentadas (NOV/2025)

As seguintes funções foram refatoradas com comentários linha por linha explicando cada etapa:

### `small_cases.c` — Trata casos de 4 e 5 elementos

- **`bring_min_to_top_and_pb(t_stack *stack)`**
  - Encontra o menor elemento em A usando `find_min_value()`.
  - Calcula a posição com `find_position()`.
  - Escolhe entre `ra` (rotações para cima) ou `rra` (rotações para baixo) conforme qual é mais curto.
  - Executa `pb` para enviar o mínimo para B.
  - **Caso 4**: remove 1 mínimo, ordena 3 em A com `sort_3()`, volta com `pa`.
  - **Caso 5**: remove 2 mínimos em sequência, ordena 3 em A, volta com dois `pa`.

- **`handle_small_cases(t_stack *stack, int size)`**
  - Detecta se o tamanho é 4 ou 5.
  - Executa a estratégia acima e retorna 1 (sucesso) ou 0 (tamanho não é 4/5).

### `pull_b.c` — Segunda fase: reinserção de B para A

- **`move_to_top_b(t_stack *stack, int position)`**
  - Traz um elemento em posição `position` de B para o topo.
  - Calcula se é mais rápido usar `rb` (rotação para cima) ou `rrb` (rotação para baixo).
  - Critério: se `position <= size/2`, usa `rb` `position` vezes; caso contrário, usa `rrb` `(size - position)` vezes.

- **`phase_pull_b_to_a(t_stack *stack, int size)`**
  - Itera de `size-1` até `0` (do maior para o menor em B).
  - Para cada valor, encontra sua posição em B com `find_position()`.
  - Move para o topo com `move_to_top_b()`.
  - Executa `pa` para trazer para A.
  - **Resultado**: A fica completamente ordenada (maiores foram inseridos primeiro, mantendo a ordem).

### `parse_index.c` — Indexação de valores (0..n-1)

- **`bubble_sort(int *arr, int n)`**
  - Ordena um array temporário usando bubble sort.
  - Usado para construir a sequência ordenada dos valores.

- **`build_sorted_array(t_dlist *a)`**
  - Copia todos os valores de A para um array dinâmico.
  - Chama `bubble_sort()` para ordenar.
  - Retorna o array ordenado (usado como referência).

- **`assign_indices(t_dlist *a, int *sorted_arr)`**
  - Percorre A e substitui cada valor pelo seu índice relativo (0..n-1).
  - Índice 0 = menor valor, índice n-1 = maior valor.
  - Essencial para estratégias de chunking e radix.

- **`ps_index_stack(t_stack *stack)`**
  - Função pública que orquestra a indexação completa.

## 12 — Verificações finais antes de submeter

1. Compilar sem warnings: `make` com `-Wall -Wextra -Werror` deve passar.
2. Norminette: corrija estilo conforme normas da 42 (nomes de funções, tamanho de linhas, arquivos, etc.).
3. Teste exaustivo para n=2..5 (todas permutações).
4. Teste com vetores maiores típicos (100 e 500) e compare com soluções públicas apenas para referência (não copie!).
5. Rodar valgrind (ou equivalente) para garantir ausência de leaks:

```bash
valgrind --leak-check=full ./push_swap 3 2 1
```

6. Certifique-se de que sua execução não imprime nada além das operações (nenhuma mensagem de debug na saída padrão).

## 13 — Erros comuns e como evitá-los

- Duplicatas não detectadas: verifique a lista inteira antes de começar a ordenar.
- Overflow ao converter argumentos: use `long` temporário.
- Operações impressas mesmo em erros: imprima `Error` apenas e encerre.
- Esquecer de atualizar `size`/`head`/`tail` em operações — causa corrupção da lista.
- Libertar memória: free em todos os paths (parsing com erro, sucesso, etc.).

## 14 — Estratégia de desenvolvimento recomendada (passo a passo)

1. Implementar parsing e validação (tests unitários simples).
2. Implementar `dlist` e operações básicas (`sa`, `pb`, `ra`, `rra`) e testar manualmente.
3. Implementar `sort_2` e `sort_3` (testar todas permutações).
4. Implementar `sort_4` e `sort_5` (usar estratégia de mover menores para B).
5. Implementar `sort_many` com radix (é a abordagem mais simples e confiável).
6. Melhorar: implementar chunking se quiser reduzir número de operações.
7. Testar exaustivamente e corrigir leaks.

## 15 — Exemplo de fluxo de execução (caso 5 elementos)

Entrada: `./push_swap 3 2 5 1 4`

- Indexe: 3->2, 2->1, 5->4, 1->0, 4->3 (índices 0..4)
- Estratégia de 5: enviar 0 e 1 para B (os dois menores), ordenar 3 em A, depois trazer B de volta.

Sequência possível (exemplo):

```
pb
pb
sa
ra
sa
pa
pa
```

Executar `./push_swap 3 2 5 1 4 | ./checker 3 2 5 1 4` deve imprimir `OK`.

ARG="3 2 1"; ./push_swap $ARG | ./checker $ARG
# 100 aleatórios
ARG="$(shuf -i 0-99 | tr "\n" " ")"; ./push_swap $ARG | ./checker $ARG
# 500 aleatórios
ARG="$(shuf -i 0-499 | tr "\n" " ")"; ./push_swap $ARG | ./checker $ARG

## 16 — Documentação do código-fonte (NOV/2025)

Todos os arquivos foram revisados e comentados com:

- **Header (`push_swap.h`)**: estruturas, enums e funções estão documentadas com explicações do que cada uma faz.
- **Funções de parsing**: comentários explicam validação, tokenização e indexação.
- **Operações (`ops_*.c`)**: cada operação documenta o comportamento (swap, push, rotate).
- **Funções de busca/utilidade**: `find_min_value`, `find_position`, `distance_to_top`, etc. explicadas.
- **Algoritmos de ordenação**: `sort_2`, `sort_3`, `sort_many` documentados com a estratégia usada.
- **Funções auxiliares refatoradas**: `small_cases.c`, `pull_b.c` com comentários linha por linha.

Para entender o fluxo completo, consulte `src/main.c`:
1. Parse argumentos e valida.
2. Indexa valores (0..n-1).
3. Escolhe algoritmo baseado no tamanho.
4. Executa ordenação.
5. Libera memória.