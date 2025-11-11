/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static int	push_single_value(char *arg, t_stack *stack)
{
	long	num; /* número como long (para detectar overflow antes de converter para int) */
	int		*value; /* ponteiro para um int que será alocado e armazenado na pilha */

	if (!is_valid_number(arg)) /* valida se o argumento é um número válido (dígitos, sinais) */
		return (0); /* retorna 0 (falha) se não é número válido */
	num = ft_atol(arg); /* converte a string para long */
	if (num > INT_MAX || num < INT_MIN) /* verifica overflow (fora do intervalo de int) */
		return (0); /* retorna 0 se estourou */
	value = malloc(sizeof(int)); /* aloca memória para um int */
	if (!value) /* se malloc falhou */
		return (0); /* retorna 0 */
	*value = (int)num; /* armazena o número (agora como int) no endereço alocado */
	ft_push_lst_dlist(stack->a, value); /* adiciona o valor (ponteiro) ao final da pilha A */
	return (1); /* retorna 1 (sucesso) */
}

int	parse_arguments(int argc, char **argv, t_stack *stack)
{
	int	i; /* índice para iterar sobre os argumentos */

	if (argc < 2) /* se não há argumentos (além do nome do programa) */
		return (0); /* retorna 0 (falha) */
	i = 1; /* começa do primeiro argumento (ignorando argv[0] = nome do programa) */
	while (i < argc) /* itera sobre todos os argumentos */
	{
		if (ps_count_words(argv[i], ' ') > 1) /* se o argumento contém múltiplas palavras (separadas por espaço) */
		{
			if (!ps_process_single_arg(argv[i], stack)) /* processa como múltiplos números em uma string */
				return (0); /* retorna 0 se falhou */
		}
		else if (!push_single_value(argv[i], stack)) /* senão, processa como um número único */
			return (0); /* retorna 0 se falhou */
		i++; /* próximo argumento */
	}
	if (ps_check_duplicates_in_stack(stack->a)) /* verifica se há duplicatas na pilha */
		return (0); /* retorna 0 se há duplicatas */
	ps_index_stack(stack); /* indexa todos os valores (0..n-1 ordenado) para facilitar radix/chunking */
	return (1); /* retorna 1 (sucesso completo) */
}
