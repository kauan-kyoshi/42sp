/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:49 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:29 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */
#include "../libft/get_next_line.h" /* inclui get_next_line para ler stdin */

int	apply_op(t_stack *stack, const char *op); /* forward declaration da função em checker_ops.c */

static int	run_checker(t_stack *stack)
{
	char	*line; /* armazena cada linha lida de stdin */
	int		count; /* conta o número de operações aplicadas */

	count = 0; /* inicializa contador */
	line = get_next_line(0); /* lê primeira linha de stdin (fd 0 = stdin) */
	while (line) /* enquanto houver linhas */
	{
		if (!apply_op(stack, line)) /* tenta aplicar a operação; se falhar retorna 0 */
			return (free(line), -1); /* libera a linha e retorna -1 (erro) */
		count++; /* incrementa contador de operações */
		free(line); /* libera a linha lida */
		line = get_next_line(0); /* lê próxima linha */
	}
	return (count); /* retorna o número total de operações aplicadas */
}

int	main(int argc, char **argv)
{
	t_stack	*stack; /* ponteiro para as duas pilhas */
	int		ops_count; /* número de operações lidas */

	if (argc < 2) /* se não há argumentos */
		return (0); /* encerra com sucesso (sem fazer nada) */
	stack = init_stack(); /* inicializa as pilhas */
	if (!stack) /* se inicialização falhou */
		return (write(2, "Error\n", 6), 1); /* imprime erro e retorna 1 */
	if (!parse_arguments(argc, argv, stack)) /* faz parsing dos argumentos */
		return (free_stack(stack), write(2, "Error\n", 6), 1); /* se falhou, limpa e retorna erro */
	ops_count = run_checker(stack); /* lê e aplica as operações de stdin */
	if (ops_count < 0) /* se run_checker retornou -1 (operação inválida) */
		return (free_stack(stack), write(2, "Error\n", 6), 1); /* imprime erro e retorna 1 */
	if (is_sorted(stack->a) && (!stack->b || stack->b->size == 0)) /* verifica se A está ordenado e B está vazio */
		ft_printf("OK (ops=%d)\n", ops_count); /* imprime OK com número de ops */
	else /* senão */
		ft_printf("KO (ops=%d)\n", ops_count); /* imprime KO com número de ops */
	free_stack(stack); /* libera toda a memória */
	return (0); /* retorna 0 (sucesso) */
}
