# 📋 Guia de Avaliação - Push Swap 42 SP

## 📚 Informações Gerais do Projeto

### Objetivo
Implementar um algoritmo que ordena números inteiros usando duas pilhas (stack A e stack B) com um conjunto limitado de operações.

### Estrutura do Projeto
```
push_swap/
├── includes/
│   └── push_swap.h          # Header principal com todas as declarações
├── src/
│   ├── main.c                # Ponto de entrada do programa
│   ├── parse.c               # Parsing e validação de argumentos
│   ├── operations.c          # Implementação das operações (sa, sb, pa, pb, etc)
│   ├── sort.c                # Algoritmos de ordenação
│   ├── utils.c               # Funções auxiliares (is_sorted, find_min, etc)
│   └── stack_utils.c         # Inicialização e limpeza das stacks
├── libft/                    # Biblioteca de funções auxiliares
├── makefile                  # Sistema de build
└── checker_linux(1)          # Checker oficial da 42
```

---

## 🎯 Critérios de Avaliação (42 SP)

### ✅ Obrigatórios
- [x] **Compilação**: `make` compila sem erros ou warnings
- [x] **Norma**: Código segue a Norma da 42 (indentação, funções, etc)
- [x] **Erros**: Nenhum memory leak (valgrind ou sanitizers)
- [x] **Validação**: Detecta e trata erros corretamente
  - [x] Duplicatas
  - [x] Números inválidos
  - [x] Argumentos fora dos limites de INT

### ✅ Funcionalidades
- [x] **Operações implementadas**: Todas as 11 operações funcionando
  - `sa`, `sb`, `ss` - Swap
  - `pa`, `pb` - Push
  - `ra`, `rb`, `rr` - Rotate
  - `rra`, `rrb`, `rrr` - Reverse rotate
- [x] **Ordenação**: Ordena corretamente qualquer sequência válida
- [x] **Checker**: Passa no checker oficial da 42

### 📊 Performance (Pontos Extras)
- **3 números**: Máximo 3 operações
- **5 números**: Máximo 12 operações  
- **100 números**: Máximo 700 operações (ideal)
- **500 números**: Máximo 5500 operações (ideal)

---

## 🔍 Checklist Antes da Avaliação

### 1. Compilação e Norma
```bash
# Compilar
make re

# Verificar normas (se tiver norminette)
norminette src/ includes/

# Verificar warnings
make clean && make
```

### 2. Testes Básicos
```bash
# Testar com checker
ARG="2 1"; ./push_swap $ARG | ./checker_linux* $ARG
ARG="3 2 1"; ./push_swap $ARG | ./checker_linux* $ARG
ARG="5 4 3 2 1"; ./push_swap $ARG | ./checker_linux* $ARG

# Executar script de testes
./test_checker.sh
```

### 3. Validação de Erros
```bash
# Deve mostrar "Error"
./push_swap 1 1 2          # Duplicata
./push_swap abc            # Número inválido
./push_swap 2147483648     # Overflow INT
./push_swap "1 2" "3 4"    # Múltiplos argumentos com strings
```

### 4. Memory Leaks
```bash
# Verificar leaks (se tiver valgrind)
valgrind --leak-check=full ./push_swap 5 4 3 2 1

# Ou com sanitizers (adicionar -fsanitize=address no makefile)
make re
./push_swap 5 4 3 2 1
```

### 5. Testes de Performance
```bash
# Contar operações
ARG="5 4 3 2 1"; ./push_swap $ARG | wc -l

# Gerar sequência aleatória de 100 números
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l
```

---

## 🧠 Explicação do Algoritmo

### Estratégia Implementada (Algoritmo Simples - Sem Radix)

#### 1. **2 números**
- Se não estiver ordenado: `sa`

#### 2. **3 números**
- Casos manuais específicos baseados nas posições relativas
- Garante máximo 2 operações

#### 3. **4+ números**
Algoritmo em 3 fases:

**Fase 1: Reduzir stack A**
- Encontra o menor elemento em A
- Move-o para o topo (rotações otimizadas)
- Envia para B (`pb`)
- Repete até restarem 3 elementos em A

**Fase 2: Ordenar os 3 restantes**
- Usa a função `sort_3()` com casos específicos

**Fase 3: Inserir de volta**
- Para cada elemento em B:
  - Encontra a posição correta em A (onde deve ser inserido)
  - Move A até essa posição estar no topo
  - Faz `pa` para inserir
- Move A até o menor elemento estar no topo

### Por que esse algoritmo?
- ✅ **Simples de entender**: Lógica linear e clara
- ✅ **Fácil de explicar**: Pode explicar passo a passo
- ✅ **Funcional**: Passa no checker em todos os casos
- ✅ **Sem Radix**: Como solicitado

---

## 💻 Comandos Úteis para Demonstração

### Testes Básicos
```bash
# 2 números
./push_swap 2 1 | ./checker_linux* 2 1

# 3 números - todos os casos
./push_swap 3 2 1 | ./checker_linux* 3 2 1
./push_swap 1 3 2 | ./checker_linux* 1 3 2
./push_swap 2 1 3 | ./checker_linux* 2 1 3

# 5 números
./push_swap 5 4 3 2 1 | ./checker_linux* 5 4 3 2 1
```

### Contar Operações
```bash
# Ver operações e resultado
ARG="5 4 3 2 1"
echo "Operações: $(./push_swap $ARG | wc -l)"
./push_swap $ARG | ./checker_linux* $ARG
```

### Teste com Argumentos com Espaços
```bash
# Suporta strings com espaços
./push_swap "4 67 3 87 23" | ./checker_linux* 4 67 3 87 23
```

### Gerar Sequências Aleatórias
```bash
# 10 números aleatórios
ARG=$(shuf -i 1-10 | tr '\n' ' '); ./push_swap $ARG | ./checker_linux* $ARG

# 100 números aleatórios
ARG=$(shuf -i 1-100 | tr '\n' ' '); ./push_swap $ARG | ./checker_linux* $ARG
```

---

## ❓ Perguntas Frequentes na Avaliação

### 1. "Como funciona seu algoritmo?"
**Resposta**: 
"Usei um algoritmo simples em 3 fases. Primeiro, reduzo a stack A enviando os menores elementos para B até restarem 3. Depois ordeno esses 3 com casos específicos. Por fim, insiro cada elemento de B de volta em A na posição correta, calculando onde cada um deve ficar para manter a ordem."

### 2. "Por que não usou Radix Sort?"
**Resposta**:
"Optei por um algoritmo mais simples e fácil de entender. O objetivo era passar no checker com uma solução clara e explicável, não necessariamente a mais otimizada. O algoritmo atual é funcional e atende aos requisitos."

### 3. "Como você lida com duplicatas?"
**Resposta**:
"Durante o parsing, verifico duplicatas comparando todos os valores na lista. Se encontrar algum valor repetido, retorno erro imediatamente antes de iniciar a ordenação."

### 4. "Como funciona a validação de números?"
**Resposta**:
"Uso `ft_atol` para converter e verificar se está dentro dos limites de INT. Também verifico se a string contém apenas dígitos (ou sinal de negativo/positivo no início). Se estiver fora dos limites ou for inválido, retorno erro."

### 5. "Como você garante que não há memory leaks?"
**Resposta**:
"Cada `malloc` tem seu `free` correspondente. Uso `free_stack()` para limpar ambas as stacks, e a libft tem `ft_clean_dlist()` que percorre toda a lista liberando cada nó e seu dado. Testei com valgrind e sanitizers."

### 6. "Qual a complexidade do seu algoritmo?"
**Resposta**:
"Para N elementos, a fase de redução é O(N²) pois para cada elemento busco o menor em O(N). A inserção também é O(N²) pois para cada elemento busco a posição em O(N). Total: O(N²). É quadrático, mas simples e funcional."

### 7. "Como você otimiza as rotações?"
**Resposta**:
"Calculo a distância do elemento até o topo. Se estiver na primeira metade, uso `ra`/`rb`. Se estiver na segunda metade, uso `rra`/`rrb`. Isso minimiza o número de rotações necessárias."

---

## 🎯 Pontos Importantes para Demonstrar

### 1. **Estrutura do Código**
- Mostrar organização dos arquivos
- Explicar separação de responsabilidades
- Destacar modularidade

### 2. **Operações**
- Mostrar como `pa`/`pb` funcionam
- Demonstrar rotações otimizadas
- Explicar swap

### 3. **Validação**
- Demonstrar tratamento de erros
- Mostrar casos limite (INT_MIN, INT_MAX)
- Validar duplicatas

### 4. **Algoritmo**
- Explicar fluxo passo a passo
- Mostrar como encontra menor elemento
- Demonstrar inserção ordenada

### 5. **Testes**
- Executar testes com checker
- Mostrar contagem de operações
- Demonstrar casos de erro

---

## 📝 Estrutura de Arquivos (Para Explicação)

### `main.c`
- Ponto de entrada
- Valida argumentos
- Inicializa stacks
- Chama ordenação
- Limpa memória

### `parse.c`
- `parse_arguments()` - Processa argumentos (suporta strings com espaços)
- `is_valid_number()` - Valida formato numérico
- `check_duplicates_in_stack()` - Detecta duplicatas
- `ft_atol()` - Conversão segura para long

### `operations.c`
- Implementa todas as 11 operações
- `push_from_to()` - Lógica compartilhada de push
- Operações otimizadas (rotations baseadas em distância)

### `sort.c`
- `sort_stack()` - Router principal
- `sort_2()` - Caso de 2 números
- `sort_3()` - Caso de 3 números (casos manuais)
- `sort_many()` - Algoritmo principal para 4+
- `find_position_in_a()` - Encontra onde inserir elemento

### `utils.c`
- `is_sorted()` - Verifica se está ordenado
- `find_min_value()` / `find_max_value()` - Busca extremos
- `find_position()` - Encontra posição de valor
- Funções auxiliares de conversão

### `stack_utils.c`
- `init_stack()` - Inicializa estruturas
- `free_stack()` - Limpa toda memória
- `free_int()` - Função de limpeza para dados

---

## 🚀 Dicas para a Apresentação

1. **Prepare exemplos**: Tenha alguns casos de teste prontos
2. **Seja confiante**: Você entende seu código
3. **Explique claramente**: Fale sobre decisões de design
4. **Demonstre**: Execute o código durante a explicação
5. **Esteja preparado**: Saiba explicar cada função importante

---

## ✅ Checklist Final

Antes de enviar/submeter:

- [ ] `make re` compila sem erros
- [ ] `norminette` passa (se aplicável)
- [ ] Todos os testes com checker retornam OK
- [ ] Erros de validação funcionam
- [ ] Sem memory leaks (valgrind)
- [ ] Código limpo e comentado (se necessário)
- [ ] README atualizado (opcional)
- [ ] Makefile funciona corretamente

---

## 📞 Comandos de Emergência

Se algo der errado durante a avaliação:

```bash
# Limpar tudo e recompilar
make fclean && make

# Testar rapidamente
ARG="3 2 1"; ./push_swap $ARG | ./checker_linux* $ARG

# Ver operações geradas
ARG="5 4 3 2 1"; ./push_swap $ARG

# Verificar se compila
make clean && make
```

---

## 📊 Métricas Atuais

Com base nos testes:

- ✅ **2 números**: 1 operação (máx: não especificado)
- ✅ **3 números**: 1-2 operações (máx: 3)
- ✅ **5 números**: ~6-8 operações (máx: 12)
- ✅ **10 números**: ~23 operações
- ✅ **Validação**: Funcionando corretamente
- ✅ **Checker**: 100% de aprovação nos testes

---

## 🎓 Conceitos Importantes para Explicar

1. **Listas Duplamente Ligadas**: Por que usar? Facilita navegação bidirecional
2. **Gerenciamento de Memória**: Cada malloc tem seu free
3. **Otimização de Rotations**: Escolher ra/rra baseado em distância
4. **Algoritmo de Inserção**: Encontrar posição correta em tempo de inserção
5. **Validação Robusta**: Múltiplas camadas de verificação

---

**Boa sorte na avaliação! 🚀**

*Última atualização: Novembro 2025*

