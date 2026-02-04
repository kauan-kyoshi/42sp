#include "gnl.h"
#include <fcntl.h>
#include <stdio.h>


int	main(void)
{
	int		fd;
	char	*line;

	/* Abre o arquivo teste.txt apenas para leitura */
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erro ao abrir o arquivo\n");
		return (1);
	}

	/* Loop simples: enquanto a função retornar algo, imprime e libera */
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}
