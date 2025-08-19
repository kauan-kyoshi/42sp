#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h> 

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("teste.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erro ao abrir o ficheiro 'teste.txt'\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(" %s", line);
		free(line);
	}
	close(fd);

	fd = open("teste2.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erro ao abrir o ficheiro 'teste.txt'\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(" %s", line);
		free(line);
	}

	close(fd);
 	return (0);
}