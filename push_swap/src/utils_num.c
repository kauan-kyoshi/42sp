/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:57 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

long	ft_atol(const char *str)
{
	long	result; /* armazena o número construído */
	int		sign; /* armazena o sinal (1 ou -1) */
	int		i; /* índice para iterar pela string */

	result = 0; /* inicia resultado em 0 */
	sign = 1; /* inicia sinal positivo */
	i = 0; /* inicia índice */
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) /* ignora espaços e tabs */
		i++; /* pula whitespace */
	if (str[i] == '-' || str[i] == '+') /* processa sinal */
	{
		if (str[i] == '-') /* se sinal é negativo */
			sign = -1; /* marca sinal como -1 */
		i++; /* avança após o sinal */
	}
	while (str[i] >= '0' && str[i] <= '9') /* processa dígitos */
	{
		result = result * 10 + (str[i] - '0'); /* adiciona o dígito ao resultado */
		if (result * sign > INT_MAX || result * sign < INT_MIN) /* verifica overflow */
			return (LONG_MAX); /* retorna LONG_MAX se estourou */
		i++; /* próximo caractere */
	}
	return (result * sign); /* retorna resultado com o sinal aplicado */
}

int	is_valid_number(char *str)
{
	int	i; /* índice para iterar pela string */

	i = 0; /* inicia índice */
	if (str[i] == '-' || str[i] == '+') /* se começa com sinal */
		i++; /* avança */
	if (!str[i] || !ft_isdigit(str[i])) /* se string é vazia ou próximo não é dígito */
		return (0); /* retorna 0 (inválido) */
	while (str[i]) /* itera pelos demais caracteres */
	{
		if (!ft_isdigit(str[i])) /* se encontrar não-dígito */
			return (0); /* retorna 0 (inválido) */
		i++; /* próximo caractere */
	}
	return (1); /* retorna 1 (número válido) */
}
