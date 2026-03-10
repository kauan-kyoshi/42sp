/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:05:32 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/02/07 23:22:13 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	i;
	int	signal;
	int	res;

	i = 0;
	signal = 1;
	res = 0;

	//primeiro loop para verificar se o caracter é um espaço ou tabulação etc...
	//caso seja, apenas ignora e passa para o proximo caracter
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}


	//segundo loop verifica o sinal, se tiver o "-" a variavel signal passa a ser -1
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			signal *= -1;
		}
		i++;
	}


	//terceiro loop verifica se o caracter é um digito
	while (str[i] >= '0' && str[i] <= '9')
	{
		// (str[i] - '0') <~ isso converte o caracter para um numero inteiro
		// (res * 10) <~ isso acrescenta 1 digito a mais
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	// no final retorna o resultado da conversão vezes o sinal(-1 se for encontrado o sinal "-")
	return (res * signal);
}
