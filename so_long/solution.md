Com certeza! Vou criar uma implementação completa e bem estruturada do projeto `so_long`, dividida em arquivos lógicos, como é esperado em um projeto da 42.

**Aviso Importante:**
*   Você precisará ter a biblioteca **MiniLibX** instalada e o caminho para ela corretamente configurado no `Makefile`.
*   Você precisará criar ou baixar as imagens (`.xpm`) para as texturas.
*   Este código assume uma implementação funcional da `libft`, incluindo `ft_printf`, `ft_str*`, `ft_split`, etc. Para a leitura do mapa, vou incluir uma implementação simples de `get_next_line` para garantir que funcione.

---

### 1. Estrutura de Arquivos

Crie a seguinte estrutura de pastas e arquivos:

```
so_long/
├── Makefile
├── includes/
│   └── so_long.h
├── libft/
│   └── (Sua biblioteca Libft aqui)
├── maps/
│   ├── valid.ber
│   ├── invalid_walls.ber
│   ├── invalid_path.ber
│   └── invalid_shape.ber
├── textures/
│   ├── wall.xpm
│   ├── floor.xpm
│   ├── player.xpm
│   ├── collectible.xpm
│   └── exit.xpm
└── src/
    ├── main.c
    ├── 01_map_reader.c
    ├── 02_map_validation.c
    ├── 03_path_validation.c
    ├── 04_graphics.c
    ├── 05_hooks.c
    ├── 06_game_logic.c
    └── 07_cleanup.c
```

---

### 2. Arquivo de Cabeçalho (`includes/so_long.h`)

Este arquivo define nossas estruturas de dados, constantes e protótipos de função.

```c
#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h" // Ajuste o caminho se necessário

// --- Constantes ---
# define TILE_SIZE 64 // Tamanho de cada tile em pixels

// Keycodes para Linux (podem variar em macOS)
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

// --- Estruturas de Dados ---

// Estrutura para guardar ponteiros de imagem
typedef struct s_img {
	void	*ptr;
	int		width;
	int		height;
}	t_img;

// Estrutura principal do jogo
typedef struct s_game {
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	collectible;
	t_img	exit;
}	t_game;

// --- Protótipos de Função ---

// 01_map_reader.c
void	read_map(char *map_file, t_game *game);

// 02_map_validation.c
void	validate_map(t_game *game);

// 03_path_validation.c
void	validate_path(t_game *game);

// 04_graphics.c
void	init_graphics(t_game *game);
void	render_map(t_game *game);

// 05_hooks.c
void	init_hooks(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close_window(t_game *game);

// 06_game_logic.c
void	move_player(t_game *game, int new_x, int new_y);

// 07_cleanup.c
void	error_exit(char *message, t_game *game);
void	clean_exit(t_game *game);
void	free_map(char **map);

#endif
```

---

### 3. Código Fonte (`src/`)

#### `main.c`
O ponto de entrada do programa. Orquestra a leitura, validação e inicialização do jogo.

```c
#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map.ber>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	read_map(argv[1], &game);
	validate_map(&game);
	validate_path(&game);
	init_graphics(&game);
	init_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
```

#### `01_map_reader.c`
Responsável por ler o arquivo `.ber` e armazená-lo em `char **map`.

```c
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
```

#### `02_map_validation.c`
Valida se o mapa é retangular, fechado por paredes e tem os componentes corretos.

```c
#include "../includes/so_long.h"

static void	check_shape_and_walls(t_game *game)
{
	int	i;

	game->map_width = ft_strlen(game->map[0]);
	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
			error_exit("Map is not rectangular.", game);
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			error_exit("Map is not enclosed by walls.", game);
		if (i == 0 || i == game->map_height - 1)
		{
			int j = 0;
			while (j < game->map_width)
			{
				if (game->map[i][j] != '1')
					error_exit("Map is not enclosed by walls.", game);
				j++;
			}
		}
		i++;
	}
}

static void	check_components(t_game *game)
{
	int	y;
	int	x;
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	game->collectibles = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				p_count++;
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map[y][x] == 'E')
				e_count++;
			else if (game->map[y][x] == 'C')
				game->collectibles++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				error_exit("Map contains invalid characters.", game);
			x++;
		}
		y++;
	}
	if (p_count != 1 || e_count != 1 || game->collectibles < 1)
		error_exit("Map must have 1 Player, 1 Exit, and at least 1 Collectible.", game);
}

void	validate_map(t_game *game)
{
	check_shape_and_walls(game);
	check_components(game);
}
```

#### `03_path_validation.c`
Usa um algoritmo de "flood fill" para garantir que todos os coletáveis e a saída são alcançáveis.

```c
#include "../includes/so_long.h"

static char	**duplicate_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!copy)
		error_exit("Memory allocation failed for map copy.", game);
	i = 0;
	while (i < game->map_height)
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			free_map(copy);
			error_exit("Memory allocation failed for map copy.", game);
		}
		i++;
	}
	return (copy);
}

static void	flood_fill(char **map_copy, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width
		|| map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, game);
	flood_fill(map_copy, x - 1, y, game);
	flood_fill(map_copy, x, y + 1, game);
	flood_fill(map_copy, x, y - 1, game);
}

static void	check_path_result(char **map_copy, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				free_map(map_copy);
				error_exit("Invalid path: Not all collectibles or exit are reachable.", game);
			}
			x++;
		}
		y++;
	}
}

void	validate_path(t_game *game)
{
	char	**map_copy;

	map_copy = duplicate_map(game);
	flood_fill(map_copy, game->player_x, game->player_y, game);
	check_path_result(map_copy, game);
	free_map(map_copy);
}
```

#### `04_graphics.c`
Inicializa a MiniLibX, carrega as texturas e desenha o mapa na tela.

```c
#include "../includes/so_long.h"

static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
		error_exit("Failed to load texture.", game);
}

void	init_graphics(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_exit("Failed to initialize mlx.", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"So Long");
	if (!game->win_ptr)
		error_exit("Failed to create window.", game);
	load_texture(game, &game->wall, "textures/wall.xpm");
	load_texture(game, &game->floor, "textures/floor.xpm");
	load_texture(game, &game->player, "textures/player.xpm");
	load_texture(game, &game->collectible, "textures/collectible.xpm");
	load_texture(game, &game->exit, "textures/exit.xpm");
}

static void	put_tile(t_game *game, char tile, int x, int y)
{
	void	*img_ptr;

	if (tile == '1')
		img_ptr = game->wall.ptr;
	else if (tile == 'P')
		img_ptr = game->player.ptr;
	else if (tile == 'C')
		img_ptr = game->collectible.ptr;
	else if (tile == 'E')
		img_ptr = game->exit.ptr;
	else // '0'
		img_ptr = game->floor.ptr;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			put_tile(game, '0', x, y); // Desenha o chão primeiro
			put_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
```

#### `05_hooks.c`
Configura e lida com os eventos de teclado e fechamento de janela.

```c
#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (keycode == KEY_ESC)
		clean_exit(game);
	else if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_A)
		x--;
	else if (keycode == KEY_S)
		y++;
	else if (keycode == KEY_D)
		x++;
	else
		return (0); // Nenhuma tecla de movimento foi pressionada
	move_player(game, x, y);
	return (0);
}

int	handle_close_window(t_game *game)
{
	clean_exit(game);
	return (0);
}

void	init_hooks(t_game *game)
{
	render_map(game); // Desenha o mapa inicial
	mlx_key_hook(game->win_ptr, handle_keypress, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close_window, game);
}
```

#### `06_game_logic.c`
Contém a lógica para mover o jogador.

```c
#include "../includes/so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	char	*next_pos;

	next_pos = &game->map[new_y][new_x];
	if (*next_pos == '1')
		return ;
	if (*next_pos == 'E' && game->collectibles == 0)
	{
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		ft_printf("Congratulations, you won!\n");
		clean_exit(game);
	}
	else if (*next_pos == 'E' && game->collectibles != 0)
		return ;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	if (*next_pos == 'C')
		game->collectibles--;
	// Atualiza o mapa de caracteres
	game->map[game->player_y][game->player_x] = '0';
	*next_pos = 'P';
	// Atualiza a posição do jogador na struct
	game->player_x = new_x;
	game->player_y = new_y;
	// Redesenha a tela
	render_map(game);
}
```

#### `07_cleanup.c`
Funções para liberar memória e sair do programa de forma limpa.

```c
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
```

---

### 4. Makefile

Este `Makefile` compilará todos os arquivos e os vinculará com a `libft` e a `minilibx`. **Ajuste `MLX_PATH` e `MLX_FLAGS` para o seu sistema.**

```Makefile
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
# --- Configuração da MiniLibX (AJUSTE PARA O SEU SISTEMA) ---
# Exemplo para Linux
MLX_PATH = ./minilibx # Supondo que a pasta da minilibx está aqui
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Exemplo para macOS
# MLX_PATH = /path/to/your/minilibx
# MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

# --- Libft ---
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# --- Arquivos Fonte ---
SRCS_DIR = src/
SRCS = main.c \
       01_map_reader.c \
       02_map_validation.c \
       03_path_validation.c \
       04_graphics.c \
       05_hooks.c \
       06_game_logic.c \
       07_cleanup.c \

# Incluir GNL se não estiver na libft
SRCS += $(LIBFT_PATH)/get_next_line.c $(LIBFT_PATH)/get_next_line_utils.c

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

# Regras
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

# Regra especial para GNL se estiver fora do SRCS_DIR
$(OBJS_DIR)get_next_line.o: $(LIBFT_PATH)/get_next_line.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJS_DIR)get_next_line_utils.o: $(LIBFT_PATH)/get_next_line_utils.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

### 5. Mapas de Exemplo (`maps/`)

**`valid.ber`**
```
1111111111
100C0001E1
10P1010001
10C00000C1
1111111111
```

**`invalid_walls.ber`** (parede aberta)
```
1111111111
100C0001E1
10P1010001
10C00000C0  <-- Parede aberta aqui
1111111111
```

**`invalid_path.ber`** (coletável inacessível)
```
1111111111
100C0001E1
10P1111001
100001C001
1111111111
```

---

### Como Usar

1.  **Texturas:** Crie 5 imagens de `64x64` pixels e salve-as como `wall.xpm`, `floor.xpm`, `player.xpm`, `collectible.xpm`, `exit.xpm` na pasta `textures/`. Você pode usar um editor de imagens como o GIMP para isso.
2.  **Bibliotecas:** Coloque sua `libft` na pasta `libft/`. Instale a `minilibx` e ajuste o `Makefile` para apontar para ela.
3.  **Compilar:** No terminal, na raiz da pasta `so_long/`, execute o comando `make`.
4.  **Executar:** Execute o jogo com um mapa como argumento: `./so_long maps/valid.ber`.