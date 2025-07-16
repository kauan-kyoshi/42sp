/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:58:55 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/09 15:53:17 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	int				result;
	unsigned int	i;

	i = 0;
	result = 0;
	while ((i < n) && (result == 0) && (s1[i] != '\0') && (s2[i] != '\0'))
	{
		result = s1[i] - s2[i];
		i++;
	}
	if ((i < n) && (result == 0) && ((s1[i] == '\0') || (s2[i] == '\0')))
	{
		result = s1[i] - s2[i];
	}
	return (result);
}
