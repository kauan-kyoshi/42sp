/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:30:58 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/25 19:22:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_calloc_bzero(void *mem, size_t size);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	allocated = malloc(size * nmemb);
	if (!allocated)
		return (NULL);
	ft_calloc_bzero(allocated, size * nmemb);
	return (allocated);
}

static void	ft_calloc_bzero(void *mem, size_t size)
{
	size_t			i;
	unsigned char	*bmem;

	i = 0;
	bmem = (unsigned char *)mem;
	while (i < size)
	{
		bmem[i] = 0;
		i++;
	}
}
