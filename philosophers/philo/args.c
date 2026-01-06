/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:38:51 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9' ); /* retorna 1 se caractere for digito decimal, 0 caso contrario */
}

static int	parse_positive_int(const char *str, int *out)
{
	long	result; /* acumulador de conversao (long para detectar overflow) */
	int		i; /* indice de iteracao sobre a string */

	if (!str || !str[0])
		return (0); /* string invalida ou vazia -> falha */
	i = 0;
	result = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0); /* caractere nao numerico -> falha */
		result = result * 10 + (str[i] - '0'); /* adiciona digito ao resultado */
		if (result > 2147483647)
			return (0); /* overflow para int -> falha */
		i++;
	}
	if (result <= 0)
		return (0); /* nao aceitamos zeros ou negativos */
	*out = (int)result; /* escreve valor convertido no ponteiro de saida */
	return (1); /* sucesso */
}

int	parse_args(int argc, char **argv, t_args *args)
{
	/* valida numero de argumentos */
	if (argc < 5 || argc > 6)
		return (0);
	/* converte e valida cada argumento posicional */
	if (!parse_positive_int(argv[1], &args->n_philo))
		return (0);
	if (!parse_positive_int(argv[2], &args->time_die))
		return (0);
	if (!parse_positive_int(argv[3], &args->time_eat))
		return (0);
	if (!parse_positive_int(argv[4], &args->time_sleep))
		return (0);
	/* argumento opcional: numero de comidas que cada filosofo deve realizar */
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5], &args->must_eat))
			return (0);
	}
	else
		args->must_eat = -1; /* -1 sinaliza que nao ha limite */
	return (1); /* argumentos validados com sucesso */
}
