Com certeza! O projeto Minitalk da 42 é um excelente exercício para entender a comunicação entre processos (IPC - Inter-Process Communication) utilizando sinais UNIX. Vou detalhar o projeto, fornecer os códigos para o cliente e o servidor, e explicar cada parte para que você possa entregá-lo com confiança.

### Visão Geral do Projeto

O objetivo do Minitalk é criar dois programas: um **servidor** e um **cliente**. O cliente enviará uma mensagem de texto para o servidor, que a receberá e a exibirá no terminal. A particularidade do projeto é que essa comunicação deve ser feita exclusivamente através dos sinais UNIX `SIGUSR1` e `SIGUSR2`.

Essencialmente, o cliente converterá cada caractere da mensagem em sua representação binária e enviará cada bit como um sinal: `SIGUSR1` para '1' e `SIGUSR2` para '0'. O servidor, por sua vez, escutará esses sinais, reconstruirá os bits em bytes (caracteres) e, ao final, imprimirá a mensagem completa.

---

### Estrutura do Projeto

Você precisará de três arquivos principais:

1.  `server.c`: O código do processo que aguardará e receberá as mensagens.
2.  `client.c`: O código do processo que enviará a mensagem.
3.  `Makefile`: Para compilar os dois programas de forma eficiente.

Vamos começar com o código de cada um.

### O Servidor (`server.c`)

O servidor é responsável por:
*   Iniciar e exibir seu PID (Process ID), para que o cliente saiba para onde enviar os sinais.
*   Configurar um "signal handler", uma função que será executada toda vez que receber `SIGUSR1` ou `SIGUSR2`.
*   Aguardar em um loop infinito por sinais.
*   Reconstruir os caracteres a partir dos bits recebidos e, ao final de uma string (marcada por um caractere nulo `\0`), imprimir a mensagem.

Aqui está o código completo para o `server.c`:

```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Função para lidar com os sinais recebidos
void	handle_signal(int signum)
{
	static unsigned char	current_char = 0;
	static int				bit_count = 0;

	// Define o bit correspondente com base no sinal recebido
	if (signum == SIGUSR1)
		current_char |= (1 << (7 - bit_count)); // Define o bit como 1

	bit_count++;

	// Quando 8 bits forem recebidos, o caractere está completo
	if (bit_count == 8)
	{
		// Se o caractere for nulo, a string terminou
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1); // Imprime o caractere

		// Reseta para o próximo caractere
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	// Imprime o PID do servidor
	printf("Server PID: %d\n", getpid());

	// Configura os handlers para os sinais SIGUSR1 e SIGUSR2
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);

	// Loop infinito para manter o servidor em execução
	while (1)
		pause(); // Aguarda por um sinal

	return (0);
}
```

#### Explicação Detalhada do `server.c`:

1.  **`#include`**:
    *   `signal.h`: Contém as funções para manipulação de sinais, como `signal()`.
    *   `unistd.h`: Fornece acesso a funções do sistema operacional POSIX, como `getpid()` e `pause()`.
    *   `stdio.h`: Para a função `printf()`.
    *   `stdlib.h`: Para funções gerais.

2.  **`handle_signal(int signum)`**:
    *   Esta é a função "signal handler". Ela é chamada pelo sistema operacional sempre que o processo recebe um sinal para o qual ela foi registrada.
    *   `static unsigned char current_char = 0;`:  Uma variável estática para construir o caractere. O valor é preservado entre as chamadas da função. `unsigned char` é usado para garantir que possamos manipular 8 bits.
    *   `static int bit_count = 0;`: Outra variável estática para contar quantos bits já recebemos para o caractere atual.
    *   `if (signum == SIGUSR1)`: Verificamos qual sinal foi recebido. Se foi `SIGUSR1`, tratamos como um bit '1'.
    *   `current_char |= (1 << (7 - bit_count));`: Esta é a parte de manipulação de bits. `(1 << (7 - bit_count))` cria uma máscara de bits. Por exemplo, no primeiro bit (bit\_count = 0), a máscara é `10000000`. No segundo (bit\_count = 1), é `01000000`, e assim por diante. O operador `|=` (OR bit a bit) "liga" o bit correspondente em `current_char` para '1'. Se o sinal for `SIGUSR2`, não fazemos nada, deixando o bit como '0' (já que `current_char` foi inicializado com 0).
    *   `bit_count++`: Incrementamos o contador de bits.
    *   `if (bit_count == 8)`: Quando recebemos 8 bits, formamos um caractere completo.
    *   `if (current_char == '\0')`: Se o caractere reconstruído for o caractere nulo, significa que a mensagem terminou, e imprimimos uma nova linha para indicar o fim.
    *   `else write(1, &current_char, 1);`: Caso contrário, imprimimos o caractere na saída padrão. `write` é uma chamada de sistema mais segura de se usar dentro de um signal handler do que `printf`.
    *   `bit_count = 0; current_char = 0;`: Resetamos as variáveis estáticas para estarmos prontos para o próximo caractere.

3.  **`main(void)`**:
    *   `printf("Server PID: %d\n", getpid());`: `getpid()` retorna o ID do processo atual. Exibimos isso para que o usuário possa passá-lo para o cliente.
    *   `signal(SIGUSR1, handle_signal);` e `signal(SIGUSR2, handle_signal);`: Aqui, registramos a função `handle_signal` para ser chamada quando recebermos `SIGUSR1` ou `SIGUSR2`.
    *   `while (1) pause();`: O servidor entra em um loop infinito. A função `pause()` suspende a execução do processo até que um sinal seja recebido. Isso é muito mais eficiente do que um loop `while(1)` vazio, pois não consome CPU.

---

### O Cliente (`client.c`)

O cliente é responsável por:
*   Receber dois argumentos da linha de comando: o PID do servidor e a string a ser enviada.
*   Iterar por cada caractere da string.
*   Para cada caractere, iterar por seus 8 bits.
*   Enviar `SIGUSR1` para um bit '1' e `SIGUSR2` para um bit '0' para o PID do servidor, usando a função `kill()`.
*   Enviar um caractere nulo (`\0`) no final para sinalizar o fim da mensagem.

Aqui está o código completo para o `client.c`:

```c
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Função para enviar um caractere bit a bit
void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		// Verifica o i-ésimo bit do caractere
		if ((c >> i) & 1)
			kill(pid, SIGUSR1); // Envia SIGUSR1 para o bit '1'
		else
			kill(pid, SIGUSR2); // Envia SIGUSR2 para o bit '0'
		usleep(100); // Pequena pausa para evitar sobrecarregar o servidor
		i--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	// Validação dos argumentos
	if (argc != 3)
	{
		write(1, "Usage: ./client [server_pid] [message]\n", 40);
		return (1);
	}

	pid = atoi(argv[1]); // Converte o PID de string para inteiro
	message = argv[2];
	i = 0;

	// Envia cada caractere da mensagem
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}

	// Envia o caractere nulo para indicar o fim da mensagem
	send_char(pid, '\0');

	return (0);
}
```

#### Explicação Detalhada do `client.c`:

1.  **`#include`**:
    *   `signal.h`: Necessário para `kill()`.
    *   `unistd.h`: Para `usleep()`.
    *   `stdlib.h`: Para `atoi()`.

2.  **`send_char(int pid, char c)`**:
    *   Esta função pega o PID do servidor e um caractere para enviar.
    *   `int i = 7;`: Começamos do bit mais significativo (o sétimo bit, já que contamos de 0 a 7).
    *   `while (i >= 0)`: Loop para percorrer os 8 bits do caractere.
    *   `if ((c >> i) & 1)`: Esta é a operação de verificação de bit. `(c >> i)` desloca os bits do caractere `c` para a direita `i` vezes. Isso coloca o bit que queremos verificar na posição mais à direita. O operador `& 1` (AND bit a bit com 1) resulta em `1` se o bit mais à direita for `1`, e `0` caso contrário.
    *   `kill(pid, SIGUSR1);` ou `kill(pid, SIGUSR2);`: A função `kill` é usada para enviar um sinal para um processo. Se o bit for '1', enviamos `SIGUSR1`; se for '0', `SIGUSR2`.
    *   `usleep(100);`:  É uma boa prática incluir uma pequena pausa (`usleep` para microsegundos) entre o envio de cada sinal. Isso dá tempo ao servidor para processar cada sinal e evita uma condição de corrida onde os sinais podem ser perdidos se enviados rápido demais.

3.  **`main(int argc, char **argv)`**:
    *   `if (argc != 3)`: Verificamos se o número de argumentos é correto. O programa espera o nome do executável, o PID do servidor e a mensagem.
    *   `pid = atoi(argv[1]);`: `atoi` converte a string do PID (que vem de `argv[1]`) para um número inteiro.
    *   `message = argv[2];`: A mensagem é o terceiro argumento.
    *   `while (message[i] != '\0')`: Percorremos a string da mensagem caractere por caractere.
    *   `send_char(pid, message[i]);`: Chamamos nossa função para enviar cada caractere.
    *   `send_char(pid, '\0');`: Após enviar todos os caracteres da mensagem, enviamos o caractere nulo (`\0`) para que o servidor saiba que a transmissão terminou.

---

### Makefile

O `Makefile` automatiza o processo de compilação.

```Makefile
NAME_SERVER = server
NAME_CLIENT = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
```

#### Explicação do `Makefile`:

*   **`NAME_...`**, **`SRCS_...`**, **`OBJS_...`**: Variáveis para os nomes dos executáveis, arquivos fonte e arquivos objeto.
*   **`CC`**, **`CFLAGS`**: Compilador e flags de compilação. `-Wall -Wextra -Werror` são as flags padrão da 42 para ativar todos os avisos e tratá-los como erros.
*   **`all`**: Regra padrão, que compila ambos, o servidor e o cliente.
*   **`$(NAME_SERVER): $(OBJS_SERVER)`**: Regra para criar o executável do servidor a partir de seus arquivos objeto.
*   **`$(NAME_CLIENT): $(OBJS_CLIENT)`**: Regra para criar o executável do cliente.
*   **`clean`**: Remove os arquivos objeto (`.o`).
*   **`fclean`**: Remove os arquivos objeto e os executáveis.
*   **`re`**: Recompila o projeto do zero.
*   **`.PHONY`**: Declara que as regras não são nomes de arquivos.

### Como Compilar e Executar

1.  Salve os códigos nos arquivos `server.c`, `client.c` e `Makefile`.
2.  Abra um terminal e execute o comando `make`. Isso irá gerar os executáveis `server` e `client`.
3.  Em um terminal, inicie o servidor:
    ```sh
    ./server
    ```
    Ele irá imprimir algo como: `Server PID: 12345`. Anote este PID.

4.  Em outro terminal, execute o cliente, substituindo `12345` pelo PID que você anotou e `"Sua mensagem aqui"` pela mensagem que deseja enviar:
    ```sh
    ./client 12345 "Olá, mundo!"
    ```
5.  No terminal do servidor, você verá a mensagem "Olá, mundo!" ser impressa caractere por caractere.

### Parte Bônus (Opcional, mas recomendado)

O projeto Minitalk também tem uma parte de bônus que geralmente inclui:

1.  **Confirmação do Cliente (ACK)**: O servidor envia um sinal de volta para o cliente para confirmar que cada bit (ou caractere) foi recebido. Isso torna a comunicação bidirecional e mais robusta.
2.  **Suporte a Unicode**: O cliente e o servidor devem ser capazes de lidar com caracteres Unicode, que podem ter mais de 8 bits.

A implementação da parte bônus exigiria uma lógica mais complexa, como usar `sigaction` em vez de `signal` para obter mais informações sobre o sinal (incluindo o PID do cliente que o enviou) e uma lógica para lidar com os múltiplos bytes de caracteres Unicode.

Espero que esta explicação detalhada e os códigos fornecidos ajudem você a concluir o projeto Minitalk com sucesso