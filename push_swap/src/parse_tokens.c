/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:33 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	ps_count_words(char const *s, char c)
{
	int	count; /* conta o número de palavras encontradas */
	int	in_word; /* flag que indica se estamos dentro de uma palavra */

	count = 0; /* inicia contagem em 0 */
	in_word = 0; /* inicia fora de uma palavra */
	while (*s) /* itera sobre cada caractere da string */
	{
		if (*s != c && !in_word) /* se o caractere não é o separador e não estamos em palavra */
		{
			in_word = 1; /* marca que entramos em uma palavra */
			count++; /* incrementa a contagem */
		}
		else if (*s == c) /* se o caractere é o separador */
			in_word = 0; /* marca que saímos da palavra */
		s++; /* próximo caractere */
	}
	return (count); /* retorna o número total de palavras */
}

int	ps_process_single_arg(char *arg, t_stack *stack)
{
	char	**split; /* array de strings resultado do split */
	int		i; /* índice para iterar sobre as strings do split */
	long	num; /* número convertido para long (para checar overflow) */
	int		*value; /* ponteiro para um int alocado */

	split = ft_split(arg, ' '); /* divide a string por espaço */
	if (!split) /* se o split falhou */
		return (0); /* retorna 0 (falha) */
	i = 0; /* inicializa índice */
	while (split[i]) /* enquanto há strings no array */
	{
		if (!is_valid_number(split[i])) /* valida se o token é um número válido */
			return (free_split(split), 0); /* libera e retorna 0 */
		num = ft_atol(split[i]); /* converte para long */
		if (num > INT_MAX || num < INT_MIN) /* verifica overflow */
			return (free_split(split), 0); /* libera e retorna 0 */
		value = malloc(sizeof(int)); /* aloca int na heap */
		if (!value) /* se malloc falhou */
			return (free_split(split), 0); /* libera e retorna 0 */
		*value = (int)num; /* armazena o número convertido */
		ft_push_lst_dlist(stack->a, value); /* adiciona à pilha A */
		i++; /* próximo token */
	}
	free_split(split); /* libera o array de strings */
	return (1); /* retorna 1 (sucesso) */
}
