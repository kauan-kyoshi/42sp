/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:22:07 by nde-sant          #+#    #+#             */
/*   Updated: 2025/06/07 15:46:46 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

int	ft_is_char_valid(char c)
{
	if ((c >= '1' && c <= '4'))
	{
		return (1);
	}
	return (0);
}

int	ft_is_input_valid(char *str)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(str);
	if (str_len < (16 * 2) - 1)
	{
		return (0);
	}
	i = 0;
	while (i < str_len)
	{
		if (ft_is_char_valid(str[i]) == 0)
		{
			return (0);
		}
		i += 2;
	}
	return (1);
}

int	opposite_pair(char c1, char c2)
{
	if ((c1 == '1' && c2 == '1'))
		return (0);
	if ((c1 == '2' && c2 == '4') || (c1 == '4' && c2 == '2')
		|| (c1 == '3' && c2 == '3'))
		return (0);
	if ((c1 == '3' && c2 == '4') || (c1 == '4' && c2 == '3'))
		return (0);
	if (c1 == '4' && c2 == '4')
		return (0);
	return (1);
}

int	valid_game(char **matrix)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (opposite_pair(matrix[0][i], matrix[1][i]) == 0)
			return (0);
		if (opposite_pair(matrix[2][i], matrix[3][i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
