# Philosophers (42) - Guia Rápido

Guia prático para implementar `philo` (parte obrigatória). Inclui o que estudar, um passo a passo e uma checklist de tarefas. Nada de código aqui.

## O que você precisa saber
- Pthreads: `pthread_create`, `pthread_join`, `pthread_detach`.
- Mutexes: `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`.
- Tempo: `gettimeofday` para timestamp em ms; `usleep` para dormir; construir `timestamp_ms()` e `msleep()` em ms.
- Concorrência: race conditions, atomicidade, dados compartilhados protegidos por mutex.
- Problemas clássicos: deadlock, livelock, starvation; estratégia pares/ímpares ou waiter para evitar deadlock.
- Gestão de recursos: alocação dinâmica, tratamento de erros de pthread/malloc, destruir mutexes, liberar memória.
- Depuração: `valgrind` (memcheck) e, se possível, `helgrind`/`drd` para data races.

## Regras importantes do subject
- Sem variáveis globais.
- Logs no formato: `<timestamp_ms> <id> <acao>` com as ações do subject.
- Mensagem de morte em até 10ms do evento real; não imprimir mais nada depois de uma morte.
- Um mutex de print para evitar sobreposição de mensagens.
- Cada filósofo é uma thread; cada garfo é um mutex; proteger acesso aos garfos.
- Libft não é permitida neste projeto; use apenas as funções autorizadas pelo subject.

## Design sugerido
- `t_table`: parâmetros (n_philos, time_to_die, time_to_eat, time_to_sleep, must_eat opcional), array de mutexes de garfo, mutex de print, mutex de estado, start_time, flags de stop.
- `t_philo`: id (1..N), idx garfo esquerdo/direito, contador de refeições, last_meal, ponteiro para `t_table`.
- Passar ponteiros para structs; nada global.

## Passo a passo (ordem sugerida)
1) Criar `Makefile` em `philo/` com `NAME = philo`, targets `all`, `clean`, `fclean`, `re`.
2) Parser de argumentos: validar inteiros positivos, tratar argumento opcional `must_eat`.
3) Utilitários de tempo: `timestamp_ms(start)` e `msleep(ms)` (loop com `usleep(500)` ou similar para precisão).
4) Inicialização: alocar `t_table`, `t_philo` array, mutexes de garfo, mutex de print/estado.
5) Logging atômico: função que tranca `print_mutex`, calcula timestamp e imprime se `stop` não foi acionado.
6) Rotina do filósofo (thread): pegar garfos (ordem anti-deadlock: pares primeiro direita, ímpares esquerda), logar, atualizar `last_meal`, comer (`msleep(time_to_eat)`), soltar, dormir, pensar.
7) Monitor: thread que varre filósofos, checa `time_to_die`, imprime `died` e seta stop; também encerra se todos atingirem `must_eat` (se dado).
8) Casos-limite: `N == 1` (pega 1 garfo, morre depois de `time_to_die`), tempos muito curtos, grandes N.
9) Encerramento limpo: sinalizar stop, juntar threads, destruir mutexes, liberar memória.
10) Testes: cenários do subject, stress com tempos curtos, Valgrind/Helgrind.

## Checklist de tarefas
- [x] Criar `philo/` e `Makefile` (NAME, all, clean, fclean, re).
- [x] Implementar parser e validações.
- [x] Implementar utilitários de tempo (`timestamp_ms`, `msleep`).
- [x] Definir `structs` (`t_table`, `t_philo`) e inicializar mutexes (implementado em `init.c`).
- [ ] Logging atômico com mutex de print (`log.c`).
- [ ] Rotina das threads com estratégia anti-deadlock (`routine.c`).
- [ ] Monitor de morte e condição `must_eat` (`monitor.c`).
- [ ] Tratar caso `N == 1`.
- [x] Destruir mutexes e liberar recursos (`cleanup.c`).
- [ ] Rodar testes + Valgrind/Helgrind.

## Dicas rápidas de testes
```bash
cd philo
make
./philo 5 800 200 200
./philo 1 800 200 200
./philo 4 310 200 100
valgrind --leak-check=full ./philo 5 800 200 200
```

