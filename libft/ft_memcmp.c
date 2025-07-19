/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:23:29 by kyoshi            #+#    #+#             */
/*   Updated: 2025/07/16 20:26:01 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*ptr;
	unsigned char		*ptr1;
	int					i;

	i = 0;
	if (n == 0)
		return (0);
	ptr = (unsigned char *)s1;
	ptr1 = (unsigned char *)s2;
	while ((ptr[i] == ptr1[i]) && n - 1 > 0)
	{
		i++;
		n--;
	}
	return ((int)(ptr[i] - ptr1[i]));
}
