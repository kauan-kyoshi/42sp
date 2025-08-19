#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h> 

int	main(void)
{
	int		fd;
	char	*line;
	int i;
	const char *arquivos[] = {"teste.txt", "teste2.txt",NULL};
	
	i=0;
	while (arquivos[i] != NULL)
	{
		fd = open(arquivos[i], O_RDONLY);
	if (fd == -1)
	{
		printf("Erro ao abrir o ficheiro \n");
		i++;
		continue;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(" %s", line);
		free(line);
	}
	close(fd);
	i++;
	}

	
 	return (0);
}