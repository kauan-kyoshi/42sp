/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:24:48 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/04/18 19:27:51 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Função que busca a primeira ocorrência de 'to_find' dentro de 'str'
// Retorna um ponteiro para o início da substring encontrada ou NULL
char	*ft_strstr(char *str, char *to_find)
{
	// Declaração de dois índices para iteração
	int	i;  // Índice para percorrer a string 'str'
	int	j;  // Índice para comparar caracteres de 'to_find'

	// Inicializa o índice de busca em 0 (começo da string)
	i = 0;

	// Verifica se 'to_find' é uma string vazia
	// Segundo a convenção de strstr(), se to_find estiver vazio, retorna 'str'
	if (to_find[0] == '\0')
	{
		return (str);
	}

	// Loop externo: percorre cada caractere de 'str' até encontrar o null terminator
	while (str[i] != '\0')
	{
		// Reinicia o índice 'j' para cada nova posição de busca
		j = 0;

		// Loop interno: compara caracteres de 'to_find' com 'str' a partir da posição 'i'
		// Continua enquanto: caracteres forem iguais E ainda haja caracteres em 'str'
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
		{
			// Verifica se chegou ao final de 'to_find'
			// Se o próximo caractere de 'to_find' for null terminator, encontrou a substring
			if (to_find[j + 1] == '\0')
			{
				// Retorna um ponteiro para a posição onde a substring foi encontrada
				return (&str[i]);
			}
			// Incrementa 'j' para comparar o próximo caractere de 'to_find'
			j++;
		}
		// Incrementa 'i' para testar a substring a partir da próxima posição
		i++;
	}

	// Se nenhuma ocorrência foi encontrada, retorna NULL (0)
	return (0);
}
