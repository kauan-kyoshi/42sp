#include "so_long.h"

// As cores na MiniLibX são representadas por inteiros.
// O formato é 0x00RRGGBB (Vermelho, Verde, Azul).
#define COR_VERMELHA 0x00FF0000

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	// 1. Inicializa a conexão
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (1);

	// 2. Cria a janela
	win_ptr = mlx_new_window(mlx_ptr, LARGURA_JANELA, ALTURA_JANELA, "Hello world!");
	if (win_ptr == NULL)
		return (1);

	// 3. Desenha um pixel na janela
	// Parâmetros: ponteiro mlx, ponteiro da janela, coordenada x, coordenada y, cor
	mlx_pixel_put(mlx_ptr, win_ptr, LARGURA_JANELA / 2, ALTURA_JANELA / 2, COR_VERMELHA);

	// 4. Inicia o loop de eventos para manter a janela aberta
	mlx_loop(mlx_ptr);
	
	return (0);
}