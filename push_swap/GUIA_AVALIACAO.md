# 📋 Guia de Avaliação - Push Swap 42 SP

## 📚 Objetivo
Ordenar números inteiros usando duas pilhas (A e B) e um conjunto limitado de operações, imprimindo a sequência mínima possível de comandos.

## 🗂️ Estrutura do Projeto
```
push_swap/
├── includes/
│   └── push_swap.h          # Header principal + helpers compartilhados
├── src/
│   ├── main.c               # Fluxo principal
│   ├── parse_main.c         # Laço de parsing
│   ├── parse_tokens.c       # split/tokenização
│   ├── parse_checks.c       # verificação de duplicatas
│   ├── parse_index.c        # compressão 0..N-1
│   ├── ops_swap.c           # sa/sb/ss
│   ├── ops_push.c + ops_push_utils.c  # pa/pb e helpers
│   ├── ops_rotate.c / ops_rev_rotate.c
│   ├── sort_small.c         # sort_2 / sort_3
│   ├── sort_many.c          # lógica de chunks 5/11
│   ├── sort_router.c        # decide qual sort usar
│   ├── utils_* (num/checks/mem/nodes/search)
│   ├── stack_utils.c        # init/free das pilhas
│   ├── checker.c            # entrada do checker local
│   └── checker_ops.c        # aplicação de operações no checker
├── libft/                    # lista duplamente ligada e utilitários
├── checker_linux(1)          # checker oficial
└── makefile                  # build
```

---

## 🎯 Critérios de Avaliação (42 SP)

### ✅ Obrigatórios
- [x] **Compilação**: `make` compila sem erros ou warnings
- [x] **Norma**: Estrutura atende à norma (faltam apenas cabeçalhos 42, a serem recolocados)
- [x] **Erros**: Sem leaks (Valgrind em casos sucesso/erro e checker)
- [x] **Validação**: Detecta e trata erros corretamente
  - [x] Duplicatas
  - [x] Números inválidos
  - [x] Argumentos fora dos limites de INT

### ✅ Funcionalidades
- [x] **Operações implementadas**: Todas as 11 operações funcionando
- [x] **Ordenação**: Ordena corretamente qualquer sequência válida
- [x] **Checker**: `checker` local e oficial funcionam

### 📊 Performance (Pontos Extras)
- **3 números**: Máx 3 operações (atinge 2)
- **5 números**: Máx 12 operações
- **100 números**: Máx 700 operações (média ~603)
- **500 números**: Máx 5500 operações (média ~5402)

---

## 🔧 Como demonstrar rapidamente
```bash
# Build (gera push_swap e checker local)
make fclean && make && make checker

# Casos simples com checker local
ARG="2 1";   ./push_swap $ARG | ./checker $ARG
ARG="3 2 1"; ./push_swap $ARG | ./checker $ARG

# 5 elementos e contagem (via checker)
ARG="5 4 3 2 1"; ./push_swap $ARG | ./checker $ARG

# Aleatórios 100/500 (ops pelo checker)
ARG="$(shuf -i 0-99  | tr '\n' ' ')";  ./push_swap $ARG | ./checker $ARG
ARG="$(shuf -i 0-499 | tr '\n' ' ')"; ./push_swap $ARG | ./checker $ARG
```

Para contar apenas as operações do `push_swap` (sem checker):
```bash
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l
```

---

## 🧠 Explicação do Algoritmo

### Estratégia Implementada
- Indexação 0..N-1 no parsing (compressão de coordenadas).
- `sort_2`/`sort_3` para casos pequenos.
- `sort_many` por chunks fixos (5 até 100; 11 acima disso).
- A→B por blocos: `pb` (+ `rb` para menores) enquanto o topo está dentro da janela do chunk atual; caso contrário `ra`.
- B→A: traz do maior para o menor com `rb/rrb` e `pa`.
- Rotação sempre pelo menor caminho (comparando com metade do tamanho da pilha).

### Por que chunks?
- Reduz rotações e limita a busca a uma janela de índices.
- Mantém B semi-organizado, barateando a reinserção.
- Heurística 5/11 mantém o total de operações dentro das metas do projeto sem precisar de radix sort.

---

## 🔒 Validação e erros
- `is_valid_number` + `ft_atol` (checa overflow) + `ps_check_duplicates_in_stack`.
- Suporte a strings com espaços em múltiplos argumentos.
- Casos testados: duplicatas, inválidos, overflow, sinal isolado, string vazia, somente espaços.

---

## 📊 Métricas Atuais (Nov/2025, pós-refatoração)
- 100 números (5 execuções): min=560, max=625, média=603.00
- 500 números (5 execuções): min=5273, max=5509, média=5402.40
- Valgrind: sem leaks em `push_swap` (caso sucesso e erro) e `checker`

---

## 🧪 Roteiro de avaliação sugerido
1. Build: `make fclean && make && make checker`
2. Casos simples: `2 1`, `3 2 1` (ver `OK (ops=X)`)
3. Validação: duplicatas, inválidos, overflow, strings com espaços
4. 5/100/500 elementos: ver `OK` e `ops`
5. Contagem direta: `./push_swap ... | wc -l`
6. (Opcional) Valgrind: `valgrind ./push_swap ...`, `valgrind ./checker ...`

---

## ❓ Perguntas comuns
- **Rotação escolhida como?** Menor caminho (`ra/rb` vs `rra/rrb`).
- **Por que indexar?** Simplifica comparações e controle dos chunks.
- **Por que `rb` após `pb`?** Mantém os menores no fundo de B, evitando trabalho na volta.
- **Complexidade?** Quadrática; suficiente para os limites da 42, fácil de explicar.

