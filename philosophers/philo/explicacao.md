# Explicação do projeto philo

**Arquivos principais**
- [philo.h](philo/philo.h): definições de estruturas e protótipos.
- [args.c](philo/args.c): parsing e validação de argumentos.
- [time_utils.c](philo/time_utils.c): utilitários de tempo (`get_time_ms`, `ft_usleep`).
- [init.c](philo/init.c): inicialização de estruturas, mutexes e filos.
- [main.c](philo/main.c): orquestração (parse → init → start threads → join → cleanup).
- [routine.c](philo/routine.c): rotina dos filósofos, aquisição/liberação de garfos, ciclo comer/dormir/pensar.
- [monitor.c](philo/monitor.c): thread monitor que detecta morte e condição de término por `must_eat`.
- [log.c](philo/log.c): funções de logging e verificação de estado (proteção de impressão).
- [cleanup.c](philo/cleanup.c): destruição de mutexes e liberação de memória.
- [enunciado.txt](philo/enunciado.txt): enunciado do projeto (requisitos).

**Mapeamento dos requisitos (enunciado → implementação)**
- Entrada: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]` — tratado em [args.c](philo/args.c).
- Sem variáveis globais: todo o estado compartilhado está encapsulado na estrutura `t_table` (definida em [philo.h](philo/philo.h)) e passada por ponteiro para os filósofos.
- Cada filósofo como uma thread: `create_thread()` em [routine.c](philo/routine.c) cria uma `pthread` por filósofo executando `philo_routine()`.
- Garfos protegidos por mutex: `t_table->forks` é um vetor de `pthread_mutex_t`, um por garfo — usado em [routine.c](philo/routine.c).
- Logs formatados: `print_status()` em [log.c](philo/log.c) imprime linhas conforme enunciado, com proteção para evitar sobreposição das mensagens.
- Detectar morte em até ~10ms: a thread monitor (em [monitor.c](philo/monitor.c)) verifica periodicamente (`usleep(500)`) e imprime morte com `state_mutex` + `print_mutex` protegidos; nas execuções feitas, a impressão ocorreu dentro do tempo esperado nas amostras testadas.
- Terminar quando todos comeram `must_eat` vezes: `must_eat` e `finished_count` em `t_table` controlam essa condição (checada em `check_finished()` em [monitor.c](philo/monitor.c)).

**Estruturas centrais (em [philo.h](philo/philo.h))**
- `t_table` — estado global compartilhado:
  - `pthread_mutex_t *forks;` — vetor de mutexes, tamanho `n_philo`.
  - `pthread_mutex_t print_mutex;` — garante impressões atômicas.
  - `pthread_mutex_t state_mutex;` — protege campos mutáveis: `stop`, `finished_count`, e leituras/escritas de `last_meal`.
  - `long long start_time;` — timestamp em ms do início da simulação.
  - `int n_philo, time_die, time_eat, time_sleep, must_eat;` — parâmetros do enunciado.
  - `int stop;` — flag (0/1) que sinaliza parada global da simulação.
  - `int finished_count;` — contador de filósofos que atingiram `must_eat` (se fornecido).

- `t_philo` — estado por filósofo:
  - `int id;` — identificador 1-based.
  - `int left, right;` — índices dos garfos esquerdo e direito no vetor `forks`.
  - `int meals;` — contador local de refeições.
  - `long long last_meal;` — timestamp em ms da última refeição (protegido por `state_mutex`).
  - `pthread_t thread;` — identificador da thread associada ao filósofo.
  - `t_table *table;` — ponteiro para a tabela compartilhada.

**Fluxo de execução (alto nível)**
1. `main()` chama `parse_args()` ([args.c](philo/args.c)) para validar entradas.
2. `init_table()` ([init.c](philo/init.c)) preenche `t_table` com os parâmetros, inicializa `forks` (vetor de mutexes), `print_mutex` e `state_mutex` e aloca o vetor `philos` (t_philo[]). Em caso de erro, limpa recursos já alocados via `clean_init_part()`.
3. `set_start_and_last_meal()` em [main.c](philo/main.c) grava `start_time` e define `last_meal = start_time` para todos os filósofos.
4. `create_thread()` ([routine.c](philo/routine.c)) cria as threads dos filósofos, cada uma executando `philo_routine()`; depois é criada a thread `monitor_routine()` ([monitor.c](philo/monitor.c)).
5. As threads filósofos executam o loop: comer → dormir → pensar, até que `sim_stopped()` retorne verdadeiro.
6. `monitor_routine()` varre filosofos periodicamente verificando:
   - se algum filósofo passou mais de `time_die` desde `last_meal` → imprime `died` e seta `stop`.
   - se `must_eat` foi especificado e `finished_count >= n_philo` → seta `stop`.
7. Quando `stop` é acionado, as threads terminam (ou são naturalmente terminadas) e `main()` faz `pthread_join()` no monitor e `join_threads()` para aguardar as threads filos terminaram; por fim chama `destroy_table()` para liberar recursos.

**Rotina do filósofo (detalhes e sincronização)**
- `philo_routine(void *arg)` (em [routine.c](philo/routine.c)):
  - Caso `n_philo == 1`: comportamento especial — pega o único garfo, imprime e dorme por `time_die` ms (não pode comer) e então libera o garfo e retorna. Esse caso evita deadlock/incertezas com um único garfo.
  - Alternância inicial: filósofos ímpares fazem `ft_usleep(1)` antes do laço para diminuir contenção inicial.
  - Laço principal: enquanto `!sim_stopped(table)`:
    - `eat(philo)`:
      - `take_forks(philo)`: estratégia anti-deadlock — filósofos pares pegam primeiro o garfo direito depois o esquerdo; ímpares fazem ordem inversa. Cada aquisição de mutex de garfo é seguida por `print_status(philo, "has taken a fork")`.
      - Ao iniciar a comida, a rotina faz `pthread_mutex_lock(&table->state_mutex)` e atualiza `philo->last_meal = get_time_ms()` e incrementa `philo->meals`. Se `philo->meals == must_eat` e `must_eat > 0`, incrementa `table->finished_count` (tudo protegido por `state_mutex`).
      - Chama `print_status(philo, "is eating")` e `ft_usleep(time_eat)`. Após dormir pelo tempo de comer, libera os dois garfos (ou o único quando `n_philo==1`).
    - Verifica `sim_stopped()` de novo (pode ter sido parada pelo monitor durante a alimentação).
    - `print_status(philo, "is sleeping")` e `ft_usleep(time_sleep)`.
    - `print_status(philo, "is thinking")` e volta ao início do laço.

- `take_forks` usa locking direto nos mutexes dos garfos sem tentativa/tentativas; a estratégia de ordering entre pares e ímpares evita deadlock circular em configurações clássicas.

**Thread monitor (detalhes e sincronização)**
- `monitor_routine(void *arg)` (em [monitor.c](philo/monitor.c)) percorre ciclicamente todos os filósofos:
  - Para cada filosofo `i`, protege leitura de `last_meal` com `state_mutex`. Em seguida obtém `now = get_time_ms()` e chama `handle_death()`.
  - `handle_death()` testa `if ((now - last) > time_die)` e, se verdadeiro, faz `pthread_mutex_lock(&state_mutex)`, verifica `if (!table->stop)` e executa: `table->stop = 1; pthread_mutex_lock(&print_mutex); printf("%lld %d died\n", now - start_time, philo->id); pthread_mutex_unlock(&print_mutex); pthread_mutex_unlock(&state_mutex);`.
  - Após varrer todos, o monitor também checa `check_finished()` (protegido por `state_mutex`) para ver se todos atingiram `must_eat` e, se sim, seta `stop`.
  - Loop tem `usleep(500)` para reduzir carga.

**Logging e ordem de locks**
- Impressões são protegidas por `print_mutex` para garantir atomicidade textual.
- Antes de imprimir, o código verifica o flag `stop` sob `state_mutex` para não imprimir estados depois do fim. A ordem utilizada é: `state_mutex` (leitura de stop) → `print_mutex` (impressão), sempre liberando na ordem inversa. Para imprimir mortes, `handle_death()` primeiro bloqueia `state_mutex`, depois `print_mutex` e printa, o que é consistente com `print_status()` (que bloqueia `state_mutex` antes de `print_mutex`), evitando inversão de ordem que poderia causar deadlock.

**Tempo e precisão**
- `get_time_ms()` (em [time_utils.c](philo/time_utils.c)) usa `gettimeofday()` e converte para ms.
- `ft_usleep(ms)` faz um loop de checagem com `usleep(500)` entre verificações para evitar busy-waiting intensa, garantindo precisão razoável para ms em escalas do enunciado.

**Tratamento de erros e limpeza**
- `init_table()` realiza alocações e inicializações; em caso de falha parcial usa `clean_init_part()` para destruir apenas os mutexes/recursos já inicializados e liberar memória parcialmente alocada.
- `destroy_table()` garante destruição de todos mutexes e liberações (forks, mutexes globais, vetor de filosofos).
- `create_thread()` se falha durante a criação de threads já alocadas, faz `pthread_join()` nas threads já criadas para não deixar threads zumbis.

**Testes já executados durante a revisão**
- `norminette` foi executado e apontou os arquivos como `OK`.
- `make` compila sem erros após as edições realizadas.
- Valgrind (memcheck) — cenários testados e resultados:
  - `./philo 1 800 200 200` — All heap blocks were freed, ERROR SUMMARY: 0 errors.
  - `./philo 4 310 200 100` — All heap blocks were freed, ERROR SUMMARY: 0 errors.
- Helgrind (detector de data-races) — cenários testados e resultado:
  - `./philo 4 310 200 100` — ERROR SUMMARY: 0 errors.
  - Execução mais longa: `./philo 5 800 200 200` com Helgrind também não mostrou erros nas execuções realizadas.

**Comandos úteis (para reproduzir)**
Executar build:

```bash
make -C philosophers/philo
```

Rodar binário:

```bash
./philo 5 800 200 200
```

Valgrind memcheck:

```bash
valgrind --leak-check=full --error-exitcode=1 ./philo 1 800 200 200
```

Helgrind (data-race detector):

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

**Casos especiais e observações**
- `n_philo == 1`: implementado caso especial para não tentar pegar dois garfos inexistentes; o filósofo pega o único garfo, imprime e espera `time_die` antes de morrer.
- Precisão de impressão da morte: monitor usa checagens periódicas; o enunciado exige impressão em até 10ms da morte real — nas execuções testadas a impressão ocorreu dentro de tempos aceitáveis; contudo, em sistemas com carga alta ou latências, o `usleep(500)` do monitor e a resolução de `ft_usleep` podem afetar este limite. Reduzir o atraso do monitor melhora a reatividade, às custas de mais CPU.
- Ordem de locks: foi tomada a decisão de proteger `stop` e `last_meal` com `state_mutex` e proteger impressão com `print_mutex`, sempre adquirindo `state_mutex` antes de `print_mutex` ao imprimir. Isso evita inversões e deadlocks conhecidos.

**Possíveis melhorias e pontos de atenção**
- Reduzir `usleep(500)` no monitor para algo menor (ex.: 100–200µs) caso precise aumentar a reatividade de morte, mas medir o custo de CPU.
- Em `ft_usleep` a resolução depende de chamadas repetidas a `gettimeofday()` + `usleep(500)` — para cenários com muitos filósofos e tempos muito pequenos, pode haver imprecisão.
- Atualmente `take_forks` usa `pthread_mutex_lock` diretamente. Uma implementação alternativa poderia usar `trylock` e backoff para reduzir contenção em cargas altas.
- Logging: o formato atual usa `printf`. Para maiores volumes / performance, buffering controlado ou escrita direta (`write`) poderia ser considerada (mas o enunciado permite `write`/`printf`).


