# ⚡ Resumo Rápido - Push Swap (estado atual)

## 🚀 Comandos Essenciais

```bash
# Compilar do zero
make fclean && make && make checker

# Teste rápido com checker (imprime OK/KO e ops)
ARG="3 2 1"; ./push_swap $ARG | ./checker $ARG

# Contar operações direto do push_swap (sem checker)
ARG="5 4 3 2 1"; ./push_swap $ARG | wc -l

# Script de testes básicos
./test_checker.sh
```

## 📁 Estrutura (o que citar na avaliação)
- `includes/push_swap.h` — tipos, protótipos e helpers compartilhados
- `src/main.c` — fluxo principal (parse → sort → free)
- Parsing (arquivos separados):
  - `parse_main.c` — laço principal
  - `parse_tokens.c`, `parse_checks.c`, `parse_index.c` — tokenização, duplicatas e indexação 0..N-1
- Operações (arquivos separados): `ops_swap.c`, `ops_push.c` + `ops_push_utils.c`, `ops_rotate.c`, `ops_rev_rotate.c`
- Ordenação: `sort_small.c` (casos 2/3), `sort_many.c` (chunks 5/11) e `sort_router.c`
- Utilitários: `utils_num.c`, `utils_checks.c`, `utils_mem.c`, `utils_nodes.c`, `utils_search.c`, `stack_utils.c`
- `checker.c` + `checker_ops.c` — checker local com contagem de operações
- `libft/` — lista duplamente ligada e utilitários de base

## 🧠 Por que usar chunks?
- Dividir a entrada em blocos pequenos aproxima a estratégia de uma inserção ordenada, mas controlando quantos elementos vão para `B` por vez.
- Ajuda a manter o número de rotações baixo: em vez de caçar o próximo menor em toda a pilha, limitamos a busca ao intervalo corrente.
- O corte em 5 ou 11 blocos é um equilíbrio clássico para `push_swap`: o suficiente para manter `B` organizado e, ao mesmo tempo, evitar overhead de cálculos mais complexos (como radix).

## 🔍 Fluxo completo do algoritmo
1. **Parsing + indexação**: valida argumentos, converte cada número para o índice relativo 0..N-1 (ordem preservada).
2. **Casos base**: N=2 ou N=3 usam funções específicas (`sort_2`, `sort_3`).
3. **Chunks A→B**:
   - `chunk_size = size / chunks` (`chunks = 5` até 100 números, `chunks = 11` acima disso).
   - `pushed_count` conta quantos índices já foram enviados.
   - Enquanto houver elementos em `A`:
     - Se topo `<= pushed_count`: o elemento é dos menores já conhecidos; fazemos `pb` + `rb` para que ele fique ao fundo de `B` (facilita a volta).
     - Se topo `<= pushed_count + chunk_size`: pertence ao bloco atual; fazemos `pb` sem rotacionar.
     - Caso contrário: `ra` para girar A até trazer um elemento do bloco corrente ao topo.
4. **Reinserção B→A**:
   - Para `value = size-1` até `0`: encontra a posição em `B` (`find_position`), traz ao topo com `move_to_top_b` e faz `pa`.
   - Resultado: `A` volta ordenada porque os maiores são inseridos primeiro e o restante já está alinhado.

## ✅ Validação (o que mostrar)
- Números inválidos e fora de INT: erro
- Duplicatas: erro
- Argumentos com espaços: suportado
- Checker local: `OK (ops=X)` / `KO (ops=Y)`

## 📊 Métricas atuais (refatoração: nov/2025)
- 100 números (5 execuções): min=560, max=625, média=603.00
- 500 números (5 execuções): min=5273, max=5509, média=5402.40
- Valgrind: sem leaks em `push_swap` (casos sucesso/erro) e `checker`

## 🧪 Demos rápidas durante a avaliação
```bash
# 3 números
ARG="3 2 1"; ./push_swap $ARG | ./checker $ARG
# 100 aleatórios
ARG="$(shuf -i 0-99 | tr "\n" " ")"; ./push_swap $ARG | ./checker $ARG
# 500 aleatórios
ARG="$(shuf -i 0-499 | tr "\n" " ")"; ./push_swap $ARG | ./checker $ARG
```

Fale com segurança: “Uso indexação 0..N-1 e chunks 5/11 para limitar o problema. Empurro A→B em blocos controlados e volto B→A trazendo sempre o maior, escolhendo `ra/rra` conforme a distância. O checker local mostra OK/KO e o total de operações; Valgrind confirma zero leaks.”
