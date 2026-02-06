#define _GNU_SOURCE // Necessário para habilitar o memmem no Linux
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	buffer[8192];      // Buffer para leitura em chunks (ajustado para 8192)
	char	*pos_match;        // Ponteiro para onde a palavra alvo foi encontrada
	char	*pos_buffer;       // Ponteiro móvel para percorrer o buffer atual
	ssize_t	chunk;             // Quantidade de bytes lidos na última chamada read
	size_t	target_len;        // Tamanho da palavra a ser filtrada
	size_t	i;                 // Contador para o loop de asteriscos
	size_t	res_len = 0;       // Tamanho do residual (sobra) que ficou no buffer

	// Validação de argumentos: precisa de exatamente 1 alvo não vazio
	if (argc != 2 || !argv[1] || !argv[1][0])
		return (1);

	target_len = strlen(argv[1]);

	// Loop principal: lê dados do stdin e coloca logo após o residual anterior
	while ((chunk = read(0, buffer + res_len, sizeof(buffer) - res_len)) > 0)
	{
		res_len += chunk;      // Atualiza o total de dados válidos no buffer
		pos_buffer = buffer;   // Reinicia o ponteiro de busca para o início do buffer

		// Busca por ocorrências enquanto houver dados suficientes para um match
		while ((pos_match = memmem(pos_buffer, res_len - (pos_buffer - buffer), argv[1], target_len)))
		{
			// Escreve tudo o que estava ANTES da palavra encontrada
			write(1, pos_buffer, pos_match - pos_buffer);

			// Substitui a palavra encontrada por asteriscos
			i = 0;
			while (i++ < target_len)
				write(1, "*", 1);

			// Move o ponteiro para depois da palavra filtrada
			pos_buffer = pos_match + target_len;
		}
		// Calcula quanto sobrou no buffer que não foi processado (fragmento final)
		res_len -= (pos_buffer - buffer);
		// Move esse residual para o início do buffer para a próxima rodada
		memmove(buffer, pos_buffer, res_len);
	}
	// Escreve o último residual que sobrou após o fim do arquivo (EOF)
	write(1, buffer, res_len);
	return (0);
}