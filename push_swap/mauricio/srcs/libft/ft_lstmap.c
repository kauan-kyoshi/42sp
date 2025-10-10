/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:01:34 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/27 18:16:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*next(t_list *lt, t_list **ax, t_list **n, void (*del)(void *))
{
	if (lt)
	{
		(*ax)->next = malloc(sizeof(t_list));
		if (!(*ax)->next)
		{
			ft_lstclear(n, del);
			return (NULL);
		}
		return ((*ax)->next);
	}
	else
	{
		(*ax)->next = NULL;
		return (*ax);
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;

	if (!lst || !f)
		return (NULL);
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	aux = new;
	while (lst)
	{
		aux->content = f(lst->content);
		if (!aux->content)
			return (ft_lstclear(&new, del), NULL);
		lst = lst->next;
		aux = next(lst, &aux, &new, del);
		if (!aux)
			return (NULL);
	}
	return (new);
}
