# Philosophers — Guia Passo a Passo

Este documento é um guia prático para implementar o projeto `philo` (obrigatório). Está escrito em português e cobre: o que aprender, projeto de alto nível, passos recomendados, casos-limite e uma checklist acionável.

**Visão Geral**
- **Objetivo:** Implementar a simulação dos filósofos usando threads e mutexes conforme o subject da 42. O binário deve se chamar `philo` e aceitar os argumentos obrigatórios.
- **Regras importantes:** sem variáveis globais; logs atômicos; mensagens seguem o formato com timestamp em ms; morte deve ser detectada com precisão (mensagem em até 10ms da morte real).

**Pré-requisitos (ferramentas)**
- **Compilador:** `gcc` (C, POSIX threads).
- **Ferramentas de depuração:** `valgrind` (memcheck), `helgrind` ou `drd` (opcional) para data races.
- **Tempo:** `gettimeofday` e `usleep` serão usados para medir/esperar em ms.

**O que aprender / revisar**
- **Pthreads:** `pthread_create`, `pthread_join`, `pthread_detach`.
- **Mutexes:** `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`.
- **Tempo em C:** como usar `gettimeofday` para timestamps, converter para milissegundos, e como implementar `msleep` com `usleep` sem perder precisão.
- **Concorrência:** race conditions, atomicidade, proteção de dados compartilhados.
- **Problemas clássicos:** deadlock, livelock, starvation; estratégias para evitá-los.
- **Gerenciamento de recursos:** alocação dinâmica, tratamento de erros, liberação correta (mutexes e memória).
- **Debug e testes:** scripts de execução, `valgrind` e ferramentas de detecção de races.

**Design sugerido (alto nível)**
- `t_table` (ou `table`): parâmetros da simulação (`n_philos`, `time_to_die`, `time_to_eat`, `time_to_sleep`, `must_eat`), array de `pthread_mutex_t` para garfos, mutex de print, timestamp de início e flags de encerramento (protegidas por mutex).
- `t_philo` (ou `philo`): id (1..N), índice do garfo esquerdo e direito, contador de refeições, timestamp da última refeição, ponteiro para `t_table`.
- Não use variáveis globais — passe ponteiros para structs para cada thread.

**Sequência de implementação (passos práticos)**
1. Criar diretório `philo/` e `Makefile` com as rules exigidas (`NAME`, `all`, `clean`, `fclean`, `re`).
2. Implementar parsing de argumentos com validação estrita (inteiros positivos), retornar erro em caso de entrada inválida.
3. Implementar utilitários de tempo:
   - função `timestamp_ms()` que retorna ms desde `start_time`.
   - função `msleep(ms)` que faz `usleep` em blocos (para evitar oversleep em casos longos).
4. Criar e inicializar `t_table` e array de `t_philo`. Inicializar mutexes (um por garfo) e um mutex `print_mutex`.
5. Implementar função de logging atômico `print_action(philo, "has taken a fork")` que bloqueia `print_mutex`, calcula timestamp e escreve a linha formattada.
6. Implementar rotina da thread do filósofo:
   - Repetir: pegar garfos, registrar `has taken a fork` duas vezes, atualizar `last_meal`, `is eating` (usar `msleep(time_to_eat)`), soltar garfos, `is sleeping` (`msleep(time_to_sleep)`), `is thinking`.
   - Estratégias para evitar deadlock: ordem diferente para filósofos pares/ímpares (pegar primeiro garfo esquerdo ou direito), ou limitar quantos podem pegar garfos simultaneamente (ex.: semáforo/waiter). Para a parte obrigatória, o padrão pares/ímpares costuma ser suficiente.
7. Implementar thread monitor (observador): periodicamente verifica `last_meal` de cada filósofo e dispara `X died` se `time_to_die` ultrapassado. Ao detectar morte, imprimir mensagem e sinalizar encerramento.
8. Implementar condição de término por `must_eat` (se argumento opcional fornecido): contador por filósofo protegido por mutex; quando todos alcançarem `must_eat`, encerrar simulação graciosamente.
9. Tratar caso especial `N == 1`: filósofo tenta pegar um garfo, não consegue pegar o segundo, deve morrer após `time_to_die` (imprimir `has taken a fork` e depois `died`).
10. Limpar: juntar threads/encerrar, destruir mutexes, liberar memória.

**Regras de logging (importante)**
- Formato: `<timestamp_in_ms> X <action>` — por exemplo: `412 3 is eating`.
- Use um único mutex para impressão para prevenir sobreposição.
- Ao detectar morte, imprimir `X died` e encerrar; não imprimir mais ações depois de uma morte.
- A mensagem de morte deve aparecer em até 10ms do evento real — por isso o monitor deve verificar com frequência suficiente (ex.: loop com `usleep(1000)` ou `usleep(500)`), sem gastar CPU excessiva.

**Técnicas para evitar problemas**
- Evitar data races: qualquer dado lido/escrito por múltiplas threads (last_meal, contador de refeições, flag de encerramento) deve ser protegido por mutex.
- Evitar deadlock: estratégia de ordenação (filósofos pares pegam primeiro o garfo direito, ímpares o esquerdo) ou um waiter.
- Precisão do tempo: `usleep` tem resolução limitada; usar pequenos sleeps em loops quando precisar de alta responsividade.

**Testes recomendados**
- Casos do subject com variações de tempos e N: exemplos típicos incluem `1 800 200 200`, `5 800 200 200`, `4 410 200 200`, `4 310 200 100`.
- Teste de estresse: aumentar `n_philos` e fazer loops com tempos curtos.
- Verificação de memória: rodar `valgrind --leak-check=full ./philo ...`.
- Verificação de race: `valgrind --tool=helgrind ./philo ...` (se disponível) ou similares.

**Makefile & Entregáveis**
- Entregar pasta `philo/` com `Makefile`, `*.c`, `*.h`.
- Regras obrigatórias no `Makefile`: `NAME = philo`, alvos `all`, `clean`, `fclean`, `re`.

**Parte bônus (opcional)**
- Implementação usando processos: cada filósofo é um processo; usar semáforos POSIX para garfos e para print; gerenciar kill/wait e comunicação entre processos.

**Checklist prática (curta)**
- [ ] Criar `philo/` e `Makefile`.
- [ ] Parser de argumentos e validação.
- [ ] Utilitários de tempo (`timestamp_ms`, `msleep`).
- [ ] Structs `t_table` e `t_philo` e inicialização de mutexes.
- [ ] Implementar logging atômico (`print_action`).
- [ ] Rotina de filósofo (com estratégia anti-deadlock).
- [ ] Thread monitor de morte e condição de término por `must_eat`.
- [ ] Tratamento de `N == 1`.
- [ ] Testes, Valgrind/Helgrind, ajustes finos.

**Comandos úteis**
Compile / testar:
```bash
cd philo
make
./philo 5 800 200 200
```

Rodar Valgrind:
```bash
valgrind --leak-check=full ./philo 5 800 200 200
```

Observações finais
- Se quiser, eu posso: gerar um `Makefile` base, esboçar as `structs` e os protótipos, ou implementar a versão obrigatória passo-a-passo. Diga qual próximo passo prefere.
