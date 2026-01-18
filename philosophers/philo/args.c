/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:38:51 by kakubo-l            #+#    #+# */
/*   Updated: 2026/01/18 01:45:55 by kakubo-l         ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: is_digit
 * Verifica se um caractere é um dígito (0-9)
 * 
 * Parâmetros:
 *   c - Caractere a ser verificado
 * 
 * Retorno:
 *   1 se é dígito, 0 caso contrário
 * ============================================================================ */
static int	is_digit(char c)
{
	return (c >= '0' && c <= '9' );  // Retorna 1 se c está entre '0' e '9'
}

/* ============================================================================
 * FUNÇÃO: parse_positive_int
 * Converte uma string em um inteiro positivo com validação
 * 
 * Parâmetros:
 *   str - String a ser convertida
 *   out - Ponteiro onde o valor convertido será armazenado
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * 
 * Validações:
 *   - String não pode ser NULL ou vazia
 *   - Todos os caracteres devem ser dígitos
 *   - O valor não pode exceder INT_MAX (2147483647)
 *   - O valor não pode ser zero ou negativo
 * ============================================================================ */
static int	parse_positive_int(const char *str, int *out)
{
	long	result;
	int		i;

	// Verifica se a string é válida (não NULL e não vazia)
	if (!str || !str[0])
		return (0);
	i = 0;
	result = 0;
	// Percorre cada caractere da string
	while (str[i])
	{
		// Verifica se o caractere atual é um dígito
		if (!is_digit(str[i]))
			return (0);  // Retorna erro se não for dígito
		// Multiplica o resultado atual por 10 e adiciona o novo dígito
		result = result * 10 + (str[i] - '0');
		// Verifica overflow (valor maior que INT_MAX)
		if (result > 2147483647)
			return (0);
		i++;
	}
	// Verifica se o valor é positivo (maior que zero)
	if (result <= 0)
		return (0);
	// Armazena o resultado convertido
	*out = (int)result;
	return (1);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: parse_args
 * Faz o parsing e validação de todos os argumentos da linha de comando
 * 
 * Formato esperado:
 *   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
 * 
 * Parâmetros:
 *   argc - Número de argumentos
 *   argv - Array de strings com os argumentos
 *   args - Estrutura onde os valores parseados serão armazenados
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * ============================================================================ */
int	parse_args(int argc, char **argv, t_args *args)
{
	// Verifica se o número de argumentos está correto (4 ou 5 + nome do programa)
	if (argc < 5 || argc > 6)
		return (0);
	// Parse do argumento 1: número de filósofos
	if (!parse_positive_int(argv[1], &args->n_philo))
		return (0);
	// Parse do argumento 2: tempo para morrer (em ms)
	if (!parse_positive_int(argv[2], &args->time_die))
		return (0);
	// Parse do argumento 3: tempo para comer (em ms)
	if (!parse_positive_int(argv[3], &args->time_eat))
		return (0);
	// Parse do argumento 4: tempo para dormir (em ms)
	if (!parse_positive_int(argv[4], &args->time_sleep))
		return (0);
	// Parse do argumento 5 (opcional): número de vezes que cada filósofo deve comer
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5], &args->must_eat))
			return (0);
	}
	else
		args->must_eat = -1;  // -1 indica que não há limite de refeições
	return (1);  // Sucesso
}
