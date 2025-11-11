/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:47:03 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui push_swap.h com os tipos e protótipos */

int	main(int argc, char **argv)
{
	t_stack	*stack; /* ponteiro para a estrutura das duas pilhas (A e B) */

	if (argc < 2) /* valida se há argumentos (sem args, não faz nada) */
		return (0); /* retorna 0 (sucesso) sem fazer nada */
	stack = init_stack(); /* aloca e inicializa as duas pilhas vazias */
	if (!stack) /* se a alocação falhou */
		return (write(2, "Error\n", 6), 1); /* imprime "Error" no stderr e retorna 1 */
	if (!parse_arguments(argc, argv, stack)) /* faz parsing e validação dos argumentos */
	{
		write(2, "Error\n", 6); /* se parsing falhou, imprime erro */
		free_stack(stack); /* libera a memória alocada para as pilhas */
		return (1); /* retorna 1 (falha) */
	}
	sort_stack(stack); /* chama a função que ordena (que escolhe o algoritmo baseado no tamanho) */
	free_stack(stack); /* libera toda a memória das pilhas e valores */
	return (0); /* retorna 0 (sucesso) */
}
