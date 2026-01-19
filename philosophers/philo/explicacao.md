# Projeto Philosophers - Explicação Completa

## 📚 Índice

1. [Visão Geral](#visão-geral)
2. [O Problema do Jantar dos Filósofos](#o-problema-do-jantar-dos-filósofos)
3. [Arquitetura da Solução](#arquitetura-da-solução)
4. [Estruturas de Dados](#estruturas-de-dados)
5. [Fluxo de Execução](#fluxo-de-execução)
6. [Sincronização e Mutexes](#sincronização-e-mutexes)
7. [Prevenção de Deadlock](#prevenção-de-deadlock)
8. [Detecção de Morte](#detecção-de-morte)
9. [Casos de Teste](#casos-de-teste)
10. [Possíveis Problemas e Soluções](#possíveis-problemas-e-soluções)

---

## 🎯 Visão Geral

Este projeto implementa uma solução para o clássico problema de concorrência conhecido como "Jantar dos Filósofos" (Dining Philosophers Problem), proposto por Edsger Dijkstra em 1965.

### Objetivos do Projeto

- **Aprender programação concorrente**: Trabalhar com threads e sincronização
- **Evitar deadlocks**: Garantir que o sistema não trave
- **Evitar race conditions**: Proteger dados compartilhados
- **Precisão de timing**: Detectar morte em até 10ms
- **Gerenciamento de recursos**: Alocar e liberar memória corretamente

### Tecnologias Utilizadas

- **Linguagem**: C (padrão ANSI)
- **Threads**: POSIX threads (pthreads)
- **Sincronização**: Mutexes (pthread_mutex_t)
- **Timing**: gettimeofday, usleep

---

## 🍝 O Problema do Jantar dos Filósofos

### Descrição do Problema

N filósofos estão sentados em uma mesa redonda. Entre cada par de filósofos há um garfo. Para comer, um filósofo precisa de DOIS garfos (esquerda e direita).

### Desafios

1. **Recurso Limitado**: Existem N filósofos mas apenas N garfos
2. **Starvation**: Um filósofo pode morrer de fome se não conseguir comer
3. **Deadlock**: Todos podem ficar travados esperando por um garfo
4. **Race Conditions**: Acesso simultâneo aos mesmos recursos

### Ciclo de Vida de um Filósofo

```
PENSAR → PEGAR GARFOS → COMER → SOLTAR GARFOS → DORMIR → (repetir)
```

### Condições de Término

A simulação termina quando:
- **Um filósofo morre**: Passou `time_to_die` ms sem comer
- **Todos comeram o suficiente**: Cada um comeu pelo menos `must_eat` vezes (se especificado)

---

## 🏗️ Arquitetura da Solução

### Estrutura de Arquivos

```
philo/
├── philo.h           # Definições de estruturas e protótipos
├── main.c            # Ponto de entrada e controle principal
├── args.c            # Parsing e validação de argumentos
├── init.c            # Inicialização de estruturas e mutexes
├── routine.c         # Rotina das threads dos filósofos
├── monitor.c         # Thread de monitoramento (detecta morte)
├── log.c             # Funções de logging thread-safe
├── time_utils.c      # Utilitários de tempo
├── cleanup.c         # Liberação de recursos
└── Makefile          # Compilação do projeto
```

### Divisão de Responsabilidades

| Arquivo | Responsabilidade |
|---------|------------------|
| **args.c** | Validar entrada do usuário |
| **init.c** | Criar e configurar recursos |
| **main.c** | Orquestrar toda a simulação |
| **routine.c** | Comportamento dos filósofos |
| **monitor.c** | Vigiar morte e fim da simulação |
| **log.c** | Imprimir mensagens de forma segura |
| **time_utils.c** | Medir tempo com precisão |
| **cleanup.c** | Limpar memória e mutexes |

---

## 📊 Estruturas de Dados

### 1. `t_args` - Argumentos da Linha de Comando

```c
typedef struct s_arg
{
    int n_philo;      // Número de filósofos
    int time_die;     // Tempo máximo sem comer (ms)
    int time_eat;     // Tempo para comer (ms)
    int time_sleep;   // Tempo para dormir (ms)
    int must_eat;     // Número mínimo de refeições (-1 = sem limite)
} t_args;
```

**Uso**: Armazena os parâmetros parseados antes de inicializar a simulação.

### 2. `t_table` - Mesa (Recursos Compartilhados)

```c
typedef struct s_table
{
    pthread_mutex_t *forks;        // Array de mutexes (um por garfo)
    pthread_mutex_t print_mutex;   // Protege printf
    pthread_mutex_t state_mutex;   // Protege variáveis de estado
    long long       start_time;    // Timestamp de início (ms)
    int             n_philo;       // Número de filósofos
    int             time_die;      // Tempo para morrer (ms)
    int             time_eat;      // Tempo para comer (ms)
    int             time_sleep;    // Tempo para dormir (ms)
    int             must_eat;      // Número de refeições necessárias
    int             stop;          // Flag de parada (1 = parar)
    int             finished_count;// Filósofos que terminaram de comer
} t_table;
```

**Uso**: Contém todos os dados compartilhados entre threads.

### 3. `t_philo` - Filósofo Individual

```c
typedef struct s_philo
{
    int         id;        // ID do filósofo (1 a n_philo)
    int         left;      // Índice do garfo esquerdo
    int         right;     // Índice do garfo direito
    int         meals;     // Número de refeições consumidas
    long long   last_meal; // Timestamp da última refeição (ms)
    pthread_t   thread;    // Thread deste filósofo
    t_table     *table;    // Referência à mesa
} t_philo;
```

**Uso**: Representa um filósofo e sua thread.

---

## 🔄 Fluxo de Execução

### 1. Inicialização (main.c)

```
main()
  ↓
parse_args()              // Valida argumentos
  ↓
init_table()              // Aloca e inicializa recursos
  ↓
set_start_and_last_meal() // Define tempo de início
  ↓
create_thread()           // Cria threads dos filósofos
  ↓
pthread_create(monitor)   // Cria thread de monitoramento
```

### 2. Execução das Threads

#### Thread do Filósofo (routine.c)

```
philo_routine()
  ↓
[Se único filósofo]
  → Pega 1 garfo
  → Espera morrer
  → FIM
  ↓
[Filósofos ímpares esperam time_eat/2] (dessincronização)
  ↓
LOOP enquanto !sim_stopped():
  → eat()                // Pega garfos, come, solta garfos
  → print "is sleeping"
  → ft_usleep(time_sleep)
  → print "is thinking"
  ↓
FIM
```

#### Thread de Monitoramento (monitor.c)

```
monitor_routine()
  ↓
LOOP infinito:
  → check_philos()       // Verifica se alguém morreu
    ├─ Se morreu: para simulação e FIM
    └─ Se vivo: continua
  → check_finished()     // Verifica se todos comeram
    ├─ Se todos comeram: para simulação e FIM
    └─ Se não: continua
  → usleep(500)          // Pequena pausa
```

### 3. Finalização

```
pthread_join(monitor)    // Aguarda monitor terminar
  ↓
join_threads()           // Aguarda filósofos terminarem
  ↓
destroy_table()          // Libera mutexes e memória
  ↓
return 0                 // Programa termina
```

---

## 🔒 Sincronização e Mutexes

### Tipos de Mutexes

Este projeto usa **3 tipos de mutexes**:

| Mutex | Propósito | Protege |
|-------|-----------|---------|
| **forks[i]** | Um por garfo | Estado do garfo (livre/ocupado) |
| **print_mutex** | Impressão | printf (evita misturar mensagens) |
| **state_mutex** | Estado compartilhado | stop, last_meal, meals, finished_count |

### Regiões Críticas

#### 1. Pegar/Soltar Garfos

```c
pthread_mutex_lock(&table->forks[left]);
pthread_mutex_lock(&table->forks[right]);
// REGIÃO CRÍTICA: filósofo está com os garfos
pthread_mutex_unlock(&table->forks[left]);
pthread_mutex_unlock(&table->forks[right]);
```

#### 2. Atualizar Estado do Filósofo

```c
pthread_mutex_lock(&table->state_mutex);
philo->last_meal = get_time_ms();  // Atualiza última refeição
philo->meals++;                     // Incrementa contador
pthread_mutex_unlock(&table->state_mutex);
```

#### 3. Imprimir Status

```c
pthread_mutex_lock(&table->state_mutex);
if (!table->stop)  // Verifica se pode imprimir
{
    pthread_mutex_lock(&table->print_mutex);
    printf("%lld %d %s\n", timestamp, id, msg);
    pthread_mutex_unlock(&table->print_mutex);
}
pthread_mutex_unlock(&table->state_mutex);
```

### Por que Múltiplos Mutexes?

- **Granularidade fina**: Menos contenção, melhor performance
- **Separação de preocupações**: Cada mutex tem uma responsabilidade clara
- **Evita deadlock**: Menos mutexes mantidos simultaneamente

---

## 🚫 Prevenção de Deadlock

### O que é Deadlock?

Deadlock ocorre quando threads ficam esperando indefinidamente por recursos que nunca serão liberados.

### Cenário de Deadlock

Imagine 3 filósofos (A, B, C):

```
A pega garfo 0 e espera garfo 1
B pega garfo 1 e espera garfo 2
C pega garfo 2 e espera garfo 0
→ DEADLOCK! Ninguém consegue prosseguir
```

### Solução Implementada

**Estratégia de Pegar Garfos Diferenciada**:

```c
if (philo->id % 2 == 0)  // Filósofos PARES
{
    pega_garfo_DIREITO();
    pega_garfo_ESQUERDO();
}
else                     // Filósofos ÍMPARES
{
    pega_garfo_ESQUERDO();
    pega_garfo_DIREITO();
}
```

### Por que Funciona?

- **Quebra simetria**: Nem todos tentam pegar garfos na mesma ordem
- **Sempre há um garfo disponível**: Pelo menos um filósofo consegue comer
- **Progresso garantido**: O sistema nunca trava completamente

### Caso Especial: 1 Filósofo

```c
if (n_philo == 1)
{
    // Pega apenas 1 garfo
    // Nunca poderá comer
    // Espera até morrer
}
```

---

## ☠️ Detecção de Morte

### Requisitos

- **Precisão**: Morte deve ser detectada em até **10ms**
- **Atomicidade**: Mensagem de morte não pode ser interrompida
- **Unicidade**: Apenas uma morte deve ser reportada

### Algoritmo de Detecção

```c
// Na thread de monitoramento
for (cada filósofo)
{
    pthread_mutex_lock(&state_mutex);
    last_meal = philo->last_meal;
    pthread_mutex_unlock(&state_mutex);
    
    now = get_time_ms();
    
    if ((now - last_meal) > time_die)
    {
        pthread_mutex_lock(&state_mutex);
        if (!stop)  // Evita múltiplas mortes
        {
            stop = 1;
            pthread_mutex_lock(&print_mutex);
            printf("%lld %d died\n", timestamp, id);
            pthread_mutex_unlock(&print_mutex);
        }
        pthread_mutex_unlock(&state_mutex);
    }
}
```

### Frequência de Verificação

```c
usleep(500);  // Verifica a cada 0.5ms
```

- **Muito rápido**: Detecta morte em < 10ms
- **Não sobrecarrega CPU**: Pequena pausa entre verificações

### Atualização de last_meal

```c
// Dentro de eat()
pthread_mutex_lock(&state_mutex);
philo->last_meal = get_time_ms();  // Atualiza ANTES de comer
pthread_mutex_unlock(&state_mutex);
```

**Crucial**: Atualiza ANTES de dormir para comer, não depois!

---

## 🧪 Casos de Teste

### Testes Obrigatórios (do Subject)

| Teste | Comando | Resultado Esperado |
|-------|---------|-------------------|
| 1 filósofo | `./philo 1 800 200 200` | Filósofo deve morrer |
| 5 filósofos | `./philo 5 800 200 200` | Ninguém deve morrer |
| 5 filósofos + limite | `./philo 5 800 200 200 7` | Para após 7 refeições cada |
| 4 filósofos (410ms) | `./philo 4 410 200 200` | Ninguém deve morrer |
| 4 filósofos (310ms) | `./philo 4 310 200 100` | Um deve morrer |

### Explicação dos Testes

#### Teste 1: `./philo 1 800 200 200`

```
1 filósofo, 800ms para morrer, 200ms comer, 200ms dormir

Fluxo:
0ms    - Filósofo 1 pega garfo
0ms    - Filósofo 1 has taken a fork
...    - Espera (nunca consegue segundo garfo)
800ms  - Filósofo 1 died
```

#### Teste 2: `./philo 5 800 200 200`

```
5 filósofos, 800ms para morrer, 200ms comer, 200ms dormir

Ciclo: comer(200) + dormir(200) = 400ms
800ms > 400ms → Tempo suficiente para comer antes de morrer
```

#### Teste 3: `./philo 5 800 200 200 7`

```
Cada filósofo deve comer 7 vezes
Simulação para quando todos atingirem 7 refeições
```

#### Teste 4: `./philo 4 410 200 200`

```
4 filósofos, 410ms para morrer

Ciclo por filósofo: ~400ms
410ms > 400ms → Margem apertada mas viável
```

#### Teste 5: `./philo 4 310 200 100`

```
4 filósofos, 310ms para morrer, 200ms comer, 100ms dormir

Ciclo TEÓRICO: 200 + 100 = 300ms
310ms - 300ms = apenas 10ms de margem!
```

**Por que um filósofo morre?**

Este teste é especialmente interessante porque demonstra o problema da **contenção de recursos**.

**Análise do Problema:**

1. **Limitação física**: Com 4 filósofos e 4 garfos, **no máximo 2 filósofos podem comer simultaneamente**
   - Cada filósofo precisa de 2 garfos
   - 4 garfos ÷ 2 garfos/filósofo = 2 filósofos comendo ao mesmo tempo

2. **O que isso significa?**
   - **2 filósofos sempre estão esperando** enquanto os outros 2 comem
   - Quando os 2 que estavam comendo terminam, os outros 2 podem começar
   - Isso cria um ciclo de espera

3. **Cronograma Real (exemplo):**

```
t=0ms    → Filósofos 2 e 4 (pares) começam a comer
         → Filósofos 1 e 3 (ímpares) esperam 100ms (dessincronização)

t=100ms  → Filósofos 1 e 3 tentam pegar garfos
         → MAS garfos ainda estão ocupados pelos filósofos 2 e 4!
         → Filósofos 1 e 3 FICAM ESPERANDO

t=200ms  → Filósofos 2 e 4 terminam de comer, soltam garfos
         → Filósofos 2 e 4 começam a dormir (100ms)
         → Filósofos 1 e 3 FINALMENTE pegam garfos e começam a comer

t=300ms  → Filósofos 2 e 4 acordam, pensam, tentam pegar garfos
         → MAS garfos estão com filósofos 1 e 3
         → Filósofos 2 e 4 ESPERAM

t=400ms  → Filósofos 1 e 3 terminam de comer (200ms depois de começar)
         → Última refeição deles foi em t=200ms
         → Próxima seria em t=200+200=400ms
         → 400ms - 200ms = 200ms desde última refeição ✓ OK

MAS... e os filósofos 2 e 4?
         → Última refeição: t=0ms (quando começaram)
         → Tentam comer de novo em t=300ms, mas esperam...
         → Conseguem garfos só em t=400ms
         → 400ms - 0ms = 400ms sem comer!
         → 400ms > 310ms → MORTE! ☠️
```

4. **Por que a margem de 10ms não é suficiente?**
   - O ciclo teórico de 300ms assume **acesso imediato aos garfos**
   - Na prática, há **tempo de espera** para conseguir ambos os garfos
   - Com 4 filósofos, a espera pode adicionar 100-200ms ao ciclo
   - 300ms + espera > 310ms → Morte inevitável

5. **Visualização do problema:**

```
Timeline de um filósofo "azarado":

0ms     ─── Come (200ms) ───┐
200ms                        │ última refeição registrada
        ─── Dorme (100ms) ───┤
300ms                        │
        ─── Pensa ───────────┤
        ─── ESPERA GARFOS ───┤ ← Tempo adicional!
310ms   ← TIME_TO_DIE        │   (Os garfos estão ocupados)
        ─── AINDA ESPERANDO ─┤
320ms+  ─── MORREU! ☠️      │
```

**Conclusão:**

Com `time_to_die = 310ms` e um ciclo de 300ms, a margem é de apenas 10ms. Como sempre há contenção (2 filósofos esperam enquanto 2 comem), o tempo de espera adicional pelos garfos faz com que pelo menos um filósofo ultrapasse os 310ms sem comer, resultando em morte.

**Este teste valida:**
- ✅ Seu programa detecta corretamente quando o tempo entre refeições é muito curto
- ✅ A contenção de recursos é tratada adequadamente
- ✅ A detecção de morte funciona com margem apertada (< 10ms de precisão)


### Testes Adicionais

```bash
# Teste de precisão (2 filósofos)
./philo 2 410 200 200

# Teste com muitos filósofos
./philo 200 410 200 200

# Teste de starvation
./philo 3 310 200 100
```

### Ferramentas de Validação

#### Data Races (Helgrind)

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

**Esperado**: Nenhuma data race detectada

#### Memory Leaks (Valgrind)

```bash
valgrind --leak-check=full ./philo 5 800 200 200
```

**Esperado**: "All heap blocks were freed"

#### DRD (Outra ferramenta de race detection)

```bash
valgrind --tool=drd ./philo 5 800 200 200
```

---

## ⚠️ Possíveis Problemas e Soluções

### Problema 1: Data Race em `stop`

**Sintoma**: Helgrind reporta race condition na variável `stop`

**Causa**: Acesso não sincronizado a `stop`

**Solução**:
```c
// ERRADO
if (table->stop)  // Sem mutex!
    return;

// CORRETO
pthread_mutex_lock(&table->state_mutex);
if (table->stop)
    return;
pthread_mutex_unlock(&table->state_mutex);
```

### Problema 2: Mensagens Misturadas

**Sintoma**: Logs aparecem embaralhados
```
150 3 has15 4 taken a forkhas taken a fork
```

**Causa**: Printf sem proteção de mutex

**Solução**: Sempre usar `print_status()` que protege com `print_mutex`

### Problema 3: Morte Não Detectada em 10ms

**Sintoma**: Morte é reportada muito tarde

**Causas Possíveis**:
- Monitor verifica muito devagar (aumentar frequência)
- `ft_usleep` impreciso (revisar implementação)
- `last_meal` atualizado no momento errado

**Solução**:
```c
// Atualizar last_meal ANTES de comer, não depois
pthread_mutex_lock(&state_mutex);
philo->last_meal = get_time_ms();  // AQUI!
pthread_mutex_unlock(&state_mutex);
ft_usleep(time_eat);  // Depois
```

### Problema 4: Deadlock

**Sintoma**: Programa trava, nada acontece

**Causas**:
- Todos filósofos pegam um garfo e esperam pelo segundo
- Ordem de locks errada causa dependência circular

**Solução**: Verificar estratégia de pegar garfos (pares vs ímpares)

### Problema 5: Memory Leak

**Sintoma**: Valgrind reporta memória não liberada

**Locais Comuns**:
- `table->forks` não liberado
- `philos` não liberado
- Mutexes não destruídos

**Solução**:
```c
void destroy_table(t_table *table, t_philo *philos)
{
    // Destruir TODOS os mutexes
    for (int i = 0; i < n_philo; i++)
        pthread_mutex_destroy(&table->forks[i]);
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->state_mutex);
    
    // Liberar TODA a memória
    free(table->forks);
    free(philos);
}
```

### Problema 6: Filósofo Morre Imediatamente

**Sintoma**: Filósofo morre em 0ms

**Causa**: `last_meal` não foi inicializado

**Solução**:
```c
// Em set_start_and_last_meal()
for (int i = 0; i < n_philo; i++)
    philos[i].last_meal = table->start_time;  // Inicializar!
```

---

## 📝 Conceitos Importantes

### Race Condition

**Definição**: Quando o resultado depende da ordem de execução de threads

**Exemplo**:
```c
// Thread A e B executam simultaneamente
count++;  // Sem proteção

// Pode resultar em:
// Thread A lê count=0
// Thread B lê count=0
// Thread A escreve count=1
// Thread B escreve count=1
// Resultado: count=1 (deveria ser 2!)
```

**Prevenção**: Usar mutexes para criar seções críticas

### Deadlock

**Condições de Coffman** (para deadlock ocorrer, TODAS devem estar presentes):

1. **Mutual Exclusion**: Recurso não pode ser compartilhado
2. **Hold and Wait**: Thread segura recursos e espera por outros
3. **No Preemption**: Recursos não podem ser forçadamente liberados
4. **Circular Wait**: Cadeia circular de espera

**Prevenção**: Quebrar pelo menos uma condição (neste projeto: Circular Wait)

### Starvation

**Definição**: Thread nunca consegue recursos necessários

**No Philosophers**: Um filósofo pode nunca conseguir ambos os garfos

**Prevenção**: 
- Dessincronização (filósofos ímpares esperam)
- Ordem diferenciada de pegar garfos

---

## 🎓 Conceitos de Threads

### Thread vs Processo

| Aspecto | Thread | Processo |
|---------|--------|----------|
| Memória | Compartilhada | Separada |
| Comunicação | Fácil (variáveis) | Difícil (IPC) |
| Criação | Rápida | Lenta |
| Overhead | Baixo | Alto |

### Funções POSIX Threads

```c
// Criar thread
pthread_create(&thread, NULL, função, argumento);

// Aguardar thread terminar
pthread_join(thread, NULL);

// Mutexes
pthread_mutex_init(&mutex, NULL);
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);
pthread_mutex_destroy(&mutex);
```

---

## 🔍 Debugging

### Ferramentas Úteis

```bash
# Compilar com debug symbols
gcc -g -pthread ...

# GDB para debugar
gdb ./philo
(gdb) run 5 800 200 200
(gdb) thread apply all bt  # Ver stack de todas threads

# Helgrind para data races
valgrind --tool=helgrind ./philo 5 800 200 200

# Callgrind para profiling
valgrind --tool=callgrind ./philo 5 800 200 200
```

### Técnicas de Debug

1. **Printf Debugging**:
```c
printf("[DEBUG] Thread %d: last_meal=%lld\n", id, last_meal);
```

2. **Assertions**:
```c
assert(philo->meals >= 0);
assert(table->n_philo > 0);
```

3. **Logs com Timestamp**:
```c
printf("[%lld] Philo %d: evento\n", get_time_ms(), id);
```

---

## 📚 Recursos de Aprendizado

### Conceitos Teóricos

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Introduction to Threads - GeeksforGeeks](https://www.geeksforgeeks.org/multithreading-c-2/)
- [Mutex Tutorial](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

### Tutoriais POSIX Threads

- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [pthread Tutorial](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)

### Debugging

- [Valgrind Quick Start](https://valgrind.org/docs/manual/quick-start.html)
- [Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html)

---

## ✅ Checklist para Avaliação

### Pré-Avaliação

- [ ] Código compila sem warnings (`-Wall -Wextra -Werror`)
- [ ] Makefile funciona corretamente (all, clean, fclean, re)
- [ ] Sem variáveis globais
- [ ] Sem memory leaks (valgrind)
- [ ] Sem data races (helgrind)

### Durante Avaliação

- [ ] `./philo 1 800 200 200` → Filósofo morre
- [ ] `./philo 5 800 200 200` → Ninguém morre
- [ ] `./philo 5 800 200 200 7` → Para após 7 refeições
- [ ] `./philo 4 410 200 200` → Ninguém morre
- [ ] `./philo 4 310 200 100` → Um morre
- [ ] Morte detectada em < 10ms (teste com 2 filósofos)
- [ ] Mensagens nunca misturadas
- [ ] Explicar uso de threads
- [ ] Explicar uso de mutexes
- [ ] Explicar prevenção de deadlock
- [ ] Explicar detecção de morte

---

## 🎯 Conclusão

Este projeto ensina conceitos fundamentais de programação concorrente:

- **Threads**: Execução paralela
- **Mutexes**: Sincronização e proteção de dados
- **Deadlock**: Como evitar travamentos
- **Race Conditions**: Como prevenir bugs de concorrência
- **Timing**: Precisão em sistemas multi-thread

Dominar estes conceitos é essencial para programação de sistemas modernos!

---

## 📞 Dúvidas Comuns

### P: Por que usar múltiplos mutexes?

**R**: Granularidade fina reduz contenção. Se usássemos um único mutex global, apenas uma thread poderia fazer qualquer coisa por vez, eliminando o paralelismo.

### P: Por que filósofos ímpares esperam?

**R**: Dessincronização. Evita que todos tentem pegar garfos simultaneamente no início.

### P: Como garantir precisão de 10ms na detecção de morte?

**R**: Monitor verifica a cada 500µs (0.5ms) e usa `get_time_ms()` preciso baseado em `gettimeofday()`.

### P: O que é uma data race?

**R**: Quando duas threads acessam a mesma variável simultaneamente e pelo menos uma escreve, sem sincronização adequada.

### P: Posso usar variáveis globais?

**R**: NÃO! O subject proíbe explicitamente. Use ponteiros para compartilhar dados.

---

**Autor**: kakubo-l  
**Data**: Janeiro 2026  
**Projeto**: 42 São Paulo - Philosophers
