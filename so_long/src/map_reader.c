#include "../includes/so_long.h"

static void	check_extension(char *map_file, t_game *game)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".ber", 5) != 0)
		error_exit("Map file must have a .ber extension.", game);
}

// Uma função para contar as linhas para alocar memória corretamente
static int	count_lines(char *map_file, t_game *game)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Could not open map file.", game);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (count == 0)
		error_exit("Map is empty.", game);
	return (count);
}

void	read_map(char *map_file, t_game *game)
{
	int		fd;
	int		i;

	check_extension(map_file, game);
	game->map_height = count_lines(map_file, game);
	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
		error_exit("Memory allocation failed for map.", game);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Could not open map file.", game);
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		// get_next_line pode manter o \n, vamos removê-lo
		if (game->map[i][ft_strlen(game->map[i]) - 1] == '\n')
			game->map[i][ft_strlen(game->map[i]) - 1] = '\0';
		i++;
	}
	close(fd);
	game->map[i] = NULL;
}