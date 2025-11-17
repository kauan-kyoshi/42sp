# Minitalk — Explicação detalhada do projeto

Este documento descreve em detalhe como o projeto funciona, o protocolo entre `client` e `server`, como cada arquivo/parte interage, as escolhas de implementação (inclusive as relacionadas ao requisito de bônus) e como testar/validar (Norminette, Valgrind, execução). O objetivo é fornecer subsídio completo para a avaliação da 42.

## Visão geral

O projeto implementa um protocolo simples cliente/servidor usando apenas sinais UNIX (SIGUSR1, SIGUSR2) para enviar bytes de texto do cliente para o servidor. O servidor imprime os bytes recebidos. A comunicação é bit-a-bit:

- O cliente envia cada byte MSB-first (bit mais significativo primeiro).
- Para cada bit o cliente envia um sinal:
  - BIT_0 = SIGUSR1
  - BIT_1 = SIGUSR2
- O servidor envia um ACK por bit para informar que pode enviar o próximo bit.
- Para indicar o fim da mensagem, o cliente envia um byte terminador `\0`; o servidor responde com um ACK de conclusão.

Arquivos principais:
- `server.c` — implementa o servidor que recebe sinais, monta bytes e imprime mensagens.
- `client.c` — implementa o cliente que converte string em bits e envia sinais, aguardando ACKs.
- `includes/minitalk.h` — macros e includes compartilhados (BT_0/BIT_1/ACK_SIGNAL/COMPLETE_ACK).
- `Makefile` — compila `libft` e liga `client` e `server`.
- `libft/` — utilitários usados (ft_printf, ft_atoi, etc.).

## Protocolo (detalhado)

1. Preparação
   - O servidor é iniciado (`./server`) e imprime o seu PID.
   - O cliente recebe o PID e a mensagem a ser enviada: `./client <pid> "mensagem"`.

2. Envio por bit (cliente)
   - Para cada caractere do string, para `i = 7..0`:
     - extrai o bit `((c >> i) & 1)`;
     - envia SIGUSR1 para 0, SIGUSR2 para 1;
     - espera por um ACK do servidor (incremento de um contador controlado por handler de sinal) antes de enviar o próximo bit.

3. No servidor (handler de sinal)
   - O handler usa `sigaction` com `SA_SIGINFO` para obter o PID do remetente (via `siginfo_t`) — isso permite atender vários clientes sequencialmente.
   - Recebe BIT_0 ou BIT_1 e monta `current_char` deslocando e acrescentando o bit;
   - Quando 8 bits são acumulados (`bit_count == 8`):
     - chama `process_full_byte(sender)` que escreve o caractere resultado com `write(1, &c, 1)` (async-signal-safe);
     - se o byte for `\0` então chama `kill(sender, COMPLETE_ACK)` para sinalizar conclusão da mensagem e reseta o estado do sender.
   - Após processar o bit/byte, o servidor envia um ACK por-bit com `kill(sender, ACK_SIGNAL)`.

4. ACKs e confiabilidade
   - Implementamos ACK por bit para sincronizar envio (o cliente só envia o próximo bit após receber o ACK), evitando perda por envio rápido demais.
   - Para o ACK de conclusão (quando byte `\0` é recebido), usamos um sinal distinto (definido como `COMPLETE_ACK`) para evitar coalescência de sinais idênticos pelo kernel.
     - Explicação: sinais não-RT (como SIGUSR1/SIGUSR2) podem ser coalescidos se enviados repetidamente em sequência. Assim, se o servidor enviasse duas vezes SIGUSR1 rapidamente o cliente poderia só perceber uma ocorrência. Para evitar esse caso crítico (o cliente espera por mais de um ACK na finalização), enviamos um ACK final com sinal distinto.

## O que é um ACK — conceito, por que e como usamos aqui

ACK vem de "acknowledgement" (confirmação). Em protocolos de comunicação, um ACK é uma notificação enviada pelo receptor para informar ao emissor que dados foram recebidos corretamente. ACKs servem para duas finalidades principais:

- Confirmação (retransmissão/fiabilidade): permitir que o emissor saiba que o receptor recebeu os dados e, se não receber ACK dentro de um tempo razoável, reenvie.
- Controle de fluxo (flow control): evitar que o emissor envie dados mais rápido do que o receptor consegue processar.

Por que usamos ACKs neste projeto

- Comunicação por sinais UNIX não fornece uma camada de transporte confiável com enfileiramento de mensagens (sinais não-RT podem ser coalescidos). Sem um mecanismo de confirmação, o cliente poderia enviar bits muito rapidamente e o servidor não acompanhar, resultando em perda ou corrupção de dados.
- Usamos ACKs por bit para garantir sincronização estrita: o cliente só envia o próximo bit quando o servidor confirmou (via sinal) que o bit anterior foi processado. Isso transforma um canal potencialmente ruidoso em um canal síncrono e estável.

Como o ACK é implementado (detalhes técnicos relevantes para avaliação)

- Sinais usados:
  - `ACK_SIGNAL` (por-bit): sinal enviado pelo servidor após processar cada bit do cliente — no código atual, mapeado para `SIGUSR1`.
  - `COMPLETE_ACK` (conclusão): sinal distinto enviado pelo servidor quando recebe o byte terminador `\0` indicando fim da mensagem — mapeado para `SIGUSR2`.

- No cliente (`client.c`):
  - existe uma variável global `volatile sig_atomic_t g_ack_count` atualizada pelo handler `ack_handler` toda vez que um ACK é recebido (seja por-bit ou de conclusão).
  - Ao enviar um bit (função `send_char`) o cliente guarda `cur_count = g_ack_count`, envia o sinal (BIT_0 ou BIT_1) e então espera até que `g_ack_count != cur_count` (ou seja, até receber um ACK). No loop por-bit usamos `pause()` para retornar quando um sinal é entregue.
  - Para a confirmação final o cliente usa `send_terminator_and_wait`, que envia o byte terminador `\0` e aguarda o número esperado de ACKs (per-bit + a ACK de conclusão). Para evitar bloqueio indefinido, esse laço final usa `usleep(1000)` com um contador de timeout.

- No servidor (`server.c`):
  - O handler de sinal reconstrói `current_char` bit-a-bit. Depois de processar cada bit (e possivelmente processar o byte quando `bit_count == 8`) o servidor chama `kill(sender, ACK_SIGNAL)` para enviar o ACK por-bit.
  - Se o byte reconstruído for `\0`, `process_full_byte` envia `kill(sender, COMPLETE_ACK)` (ACK de conclusão) e reseta o estado do cliente.

Cuidados implementados por causa das limitações de sinais

- Coalescência: para evitar que dois ACKs enviados muito próximos (por-bit e de conclusão) se mesclem no kernel e cheguem como apenas um sinal no cliente, usamos um sinal distinto para a confirmação final (`COMPLETE_ACK`).
- Ordem/raça: originalmente o servidor enviava um ACK antes de completar o processamento do byte; isso permitia que o cliente enviasse o próximo bit cedo e corrompesse o estado do servidor. A correção foi enviar o ACK somente depois do processamento do bit/byte.
- Segurança do handler: o handler usa apenas variáveis `sig_atomic_t` e funções async-signal-safe (`write`, `kill`) — isso evita comportamento indefinido em handlers de sinal.
- Timeout e retransmissão: o cliente implementa timeout no aguardo da confirmação final (evita travamento). Para maior robustez pode-se implementar retransmissão ao não receber ACKs no tempo esperado.

Resumo: o ACK transforma a troca de sinais (que por si só é frágil) em um protocolo sincronizado e previsível, fornecendo confirmação e controle de fluxo; as escolhas de sinais, bloqueio e ordem de envio foram feitas para minimizar coalescência e condições de corrida.

## Segurança de sinal e regras async-signal-safe

- Dentro do handler **são usados apenas** tipos `volatile sig_atomic_t` para variáveis compartilhadas com o resto do programa — acesso seguro em signal handlers.
- São chamadas somente funções async-signal-safe dentro do handler e da rotina `process_full_byte`:
  - `write(2)`, `kill`, e manipulações simples de inteiros (sig_atomic_t).
- Bloqueamos SIGUSR1 e SIGUSR2 no `sa_mask` da `sigaction` para evitar reentrância aninhada do handler que pudesse corromper o estado.

## Justificativa das variáveis globais

- `g_state` (em `server.c`) e `g_ack_count` (em `client.c`) são globais do tipo `sig_atomic_t` para que o handler de sinal possa acessá-las de forma segura. Este uso é permitido pelo enunciado do projeto e é um padrão aceitável em implementações de sinal.

### Por que precisamos de variáveis globais e por que são seguras aqui

1) Por que variáveis locais (na pilha) NÃO serviriam

- Um handler de sinal pode ser invocado a qualquer momento, interrompendo a execução normal da thread e usando a pilha atual. Se o handler referenciar variáveis locais de uma função que foi interrompida, o acesso pode ser inseguro — especialmente se a função que declarou a variável já tiver retornado e a memória da pilha tiver sido reutilizada.
- Além disso, se o programa principal estiver atualizando a mesma variável sem proteção e o handler também a alterar, pode ocorrer corrida de dados. Variáveis locais que não são voláteis e atômicas não fornecem a garantia necessária para operações interrompíveis por sinais.

2) Por que `volatile sig_atomic_t` é a escolha correta aqui

- `sig_atomic_t` é um tipo inteiro garantido pela especificação C como sendo acessível de forma atômica em presença de sinais: leitura e escrita de um objeto `sig_atomic_t` não serão interrompidas por um handler de sinal que modifica o mesmo objeto. Isso evita meias-escritas e leituras inconsistentes.
- A qualificação `volatile` indica ao compilador que o valor pode mudar a qualquer momento fora do fluxo normal (por exemplo, por um handler), então o compilador não otimizará leituras/escritas para registradores ou removerá acessos aparentemente "redundantes" — o que é essencial para que o loop de espera do cliente veja as mudanças feitas pelo handler.

3) Como usamos essas propriedades na prática neste projeto

- Em `client.c`: `g_ack_count` é incrementado apenas pelo handler `ack_handler` (que é executado em contexto de sinal) e lido pelo código de envio no contexto normal. O uso de `volatile sig_atomic_t` garante que incrementos do handler sejam visíveis ao código que espera por ACKs e que a leitura/escrita sejam atômicas o suficiente para o propósito.
- Em `server.c`: `g_state` é uma struct cujos campos são todos `volatile sig_atomic_t`. Isso permite que o handler atualize `client_pid`, `current_char` e `bit_count` sem depender de operações não-atemporais. Observação: embora cada campo seja atômico, mutações que envolvam múltiplos campos (por exemplo, resetar `current_char` e `bit_count` juntos) não são uma operação atômica única; por isso bloqueamos sinais no `sa_mask` (ou garantimos que os pontos onde o programa fora do handler modifica o mesmo estado façam-no com sinais bloqueados) para evitar leituras/escritas simultâneas.

4) Por que não usar ponteiros ou alocação dinâmica para passar estado ao handler

- Você não pode passar parâmetros arbitrários ao handler quando ele é chamado pelo kernel (exceto via `siginfo_t` que contém metadados como `si_pid` e `si_value` quando se usa `sigqueue`). Depender de ponteiros que sejam alocados em tempo de execução e lidos pelo handler introduz riscos adicionais (por exemplo, a memória pode ser liberada, ou o ponteiro estar temporariamente inválido quando o handler for disparado).
- Portanto, guardar o estado acessível globalmente em variáveis `sig_atomic_t` é a estratégia mais simples e segura para este tipo de protocolo baseado em sinais.

5) Boas práticas e limitações

- Nunca chame funções não-async-signal-safe no handler (por exemplo `malloc`, `printf`, `ft_printf`, `str*`); usamos `write` e `kill`, que são seguros.
- Evite operações composta não-atômicas no handler; se precisar fazer atualizações consistentes de múltiplos campos do estado, bloqueie sinais temporariamente no código que modifica o estado fora do handler (ou no próprio handler, dependendo do design).
- `sig_atomic_t` pode ser pequeno (por exemplo, 32 bits); se precisar de contadores muito grandes ou dados complexos, considere outra estratégia (sockets locais, pipe self-pipe, ou sinais em tempo-real com enfileiramento).

6) Conclusão

- As variáveis globais `sig_atomic_t` usadas aqui são necessárias porque o mecanismo de entrega de sinal pode interromper o fluxo normal a qualquer momento, e precisamos de um local de estado acessível de forma segura e previsível tanto pelo handler quanto pelo restante do programa. Sem esse mecanismo, o handler teria que depender de estruturas locais instáveis ou de operações não-async-signal-safe, o que levaria a comportamento indefinido e perda/corrupção de dados.

## Implementação do cliente (detalhes)

- `parse_args` — valida argumentos, registra handlers de ACK (agora o cliente escuta dois sinais: `ACK_SIGNAL` e `COMPLETE_ACK`).
- `send_char` — envia os 8 bits do caractere e, após cada bit, espera pelo incremento do contador de ACKs (o handler `ack_handler` incrementa `g_ack_count`). Para espera, o código usa `pause()` no laço por bit para ser reativado apenas por sinais.
- `send_terminator_and_wait` — envia o `\0` e aguarda o número esperado de ACKs (por segurança, cliente espera 9 ACKs além do último contado, para contabilizar per-bit + completion). O loop de espera final foi implementado com `usleep(1000)` e contador de timeout para evitar bloqueio indefinido — isso soluciona hangs observados quando um ACK final era perdido.

## Implementação do servidor (detalhes)

- `handler` — atualiza `g_state` com cada bit recebido; quando fecha um byte chama `process_full_byte`.
- `process_full_byte` — escreve o caractere na saída. Se o caractere for `\0`, envia `COMPLETE_ACK` e reseta `g_state.client_pid`.
- `main` — configura `sigaction` (bloqueando SIGUSR1/SIGUSR2 no mask), imprime `Server PID` com `ft_printf` e entra em loop infinito.

## Bônus implementados (como foram feitos)

Parte Bônus solicitada (lista):
- O servidor deve confirmar cada mensagem recebida enviando um sinal para o cliente.
- Suporte a caracteres Unicode!

Como isso foi implementado aqui:

1) Confirmação de cada mensagem recebida (ACK de conclusão)
- Para cumprir o requisito, o servidor envia um sinal de confirmação de mensagem quando recebe o byte terminador (`\0`).
- Implementação:
  - Quando `current_char == 0` dentro de `process_full_byte`, o servidor chama `kill(sender, COMPLETE_ACK)`.
  - O cliente escuta `COMPLETE_ACK` além do ACK por-bit e assim consegue detectar a confirmação final da mensagem.
- Observações técnicas: para evitar problemas de coalescência entre dois ACKs consecutivos, `COMPLETE_ACK` foi mapeado para um sinal distinto (`SIGUSR2` — ver `includes/minitalk.h`) enquanto que o ACK por-bit usa `SIGUSR1`. Essa separação garante que o cliente receba ambas notificações.

2) Suporte a caracteres Unicode
- O protocolo envia bytes brutos. Unicode (UTF-8) é uma codificação de múltiplos bytes por caractere — não há nenhuma lógica de “caractere Unicode” no protocolo, apenas envio de bytes, por isso o UTF-8 funciona naturalmente.
- Implementação/Explicação:
  - O cliente percorre cada caractere da `C-string` (UTF-8 em memória) e envia o valor de cada `unsigned char` como 8 bits.
  - O servidor reconstroi os bytes e faz `write(1, &c, 1)` por byte.
  - O receptor (terminal) decodifica os bytes exibidos como UTF-8, desde que o locale/terminal esteja configurado para UTF-8.
- Limitações:
  - Mensagens que contenham o byte `0x00` embutido (NUL) não podem ser transmitidas porque `client` usa uma C-string terminada em NUL para decidir o fim da mensagem.
  - O protocolo não faz validação do fluxo UTF-8; se bytes inválidos chegarem, o servidor os imprimirá igualmente.

## Ajustes de robustez e escolhas feitas

- Timeout no cliente: implementado um limite para a espera final (2000 × 1 ms ≈ 2s) para evitar bloqueios indefinidos.
- Evitamos chamar funções não-async-signal-safe dentro do handler (não usamos `printf` no handler, apenas `write`).
- Usamos `sigaddset` para bloquear sinais no handler (evita reentrância e condições de corrida).
- Para contornar a coalescência de sinais não-RT, usamos sinal distinto para confirmação final (COMPLETE_ACK).
- Modificações para passar Norminette: várias refatorações de escopo de variáveis, extração de função de espera, inline de trecho de envio para reduzir número de funções e remoção de comentários em escopo inválido.

## Como compilar e rodar (passos reproducíveis)

1. Compilar:
```sh
cd /nfs/homes/kakubo-l/Kyoshi/42sp/minitalk
make
```

2. Iniciar servidor (num terminal):
```sh
./server
# saída esperada: "Server PID: <pid>"
```

3. Rodar cliente (outro terminal):
```sh
./client <server_pid> "Sua mensagem UTF-8 aqui"
```

4. Testes úteis:
- Teste Unicode:
```sh
./client <server_pid> "Olá ñ á € 漢字 テスト"
```
- Teste com timeout (evita travamento do terminal principal):
```sh
timeout 5s ./client <server_pid> "mensagem de teste"
```

## Verificações realizadas durante desenvolvimento

- Norminette: o código foi ajustado para passar nas regras aplicadas localmente (mover declarações para o topo, evitar comentários em escopo inválido, remover linhas longas, reduzir número de funções por arquivo quando necessário).
- Valgrind: executei o `client` sob Valgrind em testes, e o relatório indicou `All heap blocks were freed -- no leaks are possible` (nenhum leak detectado nas execuções rápidas que rodei).

Comandos úteis para depuração:
```sh
# rebuild
make re

# rodar servidor em background e logar
nohup ./server > server.log 2>&1 & echo $!

# rodar client com valgrind
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_client.log ./client <pid> "msg"

# mostrar log do servidor
tail -n 200 server.log
```

## Possíveis melhorias (sugestões para aprimorar a confiabilidade e features)

- Retransmissão: implementar retransmissão de bytes quando o cliente não receber o ACK no tempo esperado (ex.: reenviar o byte N vezes antes de abortar). Isso aumenta a robustez contra perda de sinais.
- Sinais em tempo-real (SIGRTMIN+n): usar sinais RT enfileirados para evitar coalescência de sinais — isso simplifica muito contar ACKs, pois múltiplas ocorrências do mesmo sinal são entregues separadamente. Observação: sinais RT nem sempre são permitidos em todos os ambientes da 42, verifique regras da avaliação.
- Suporte a entrada binária: aceitar `--file <path>` no cliente e transmitir o conteúdo binário, enviando primeiro o tamanho, ou já incluindo protocolo de length-prefix para permitir bytes NUL embutidos.
- Verificação UTF-8: validar a sequência UTF-8 recebida antes de imprimir, para detectar mensagens malformadas.

## Considerações finais (para a avaliação)

- O servidor e cliente aqui implementados seguem os requisitos mandatórios do projeto: comunicação via sinais, bit-a-bit, e impressão de mensagens.
- Os bônus solicitados foram implementados:
  - confirmação por mensagem (ACK de conclusão) — via `COMPLETE_ACK`;
  - suporte a Unicode — transmitido implicitamente por envio byte-a-byte (UTF-8 funciona sem alterações ao protocolo).
- Foram aplicadas correções de confiabilidade (bloqueio de sinais no handler, envio de ACK após processamento do byte) e melhorias de segurança de sinal.

Se quiser, eu adapto este documento para um `README.md` mais curto que ficará no repositório principal (ou eu atualizo o `PROJECT.md`) — também posso abrir um commit/PR com as alterações de código e este documento como justificativa. Quer que eu:

- coloque este documento em `README.md` (substituindo ou complementando o existente)?
- acrescente um script de testes automatizados que envia mensagens Unicode, longas, e verifica `server.log`?
- implemente retransmissão / timeout configurável no `client`?

---

Arquivo gerado automaticamente: `PROJECT_EXPLAINED.md` (no diretório raiz do projeto).