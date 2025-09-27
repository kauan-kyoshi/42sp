#include "../includes/so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	error_exit(char *message, t_game *game)
{
	if (game->map)
		free_map(game->map);
	ft_printf("Error\n%s\n", message);
	exit(1);
}

void	clean_exit(t_game *game)
{
	if (game->wall.ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall.ptr);
	if (game->floor.ptr)
		mlx_destroy_image(game->mlx_ptr, game->floor.ptr);
	if (game->player.ptr)
		mlx_destroy_image(game->mlx_ptr, game->player.ptr);
	if (game->collectible.ptr)
		mlx_destroy_image(game->mlx_ptr, game->collectible.ptr);
	if (game->exit.ptr)
		mlx_destroy_image(game->mlx_ptr, game->exit.ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		// Dependendo da versão da mlx, pode ser mlx_destroy_display
		// ou apenas liberar o mlx_ptr.
		// Em Linux, mlx_destroy_display é necessário.
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_map(game->map);
	exit(0);
}