/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 23:35:18 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/13 17:37:23 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*placen;

	if (!lst)
		return (NULL);
	placen = f(lst);
	first = placen;
	while (lst->next)
	{
		placen->next = f(lst->next);
		placen = placen->next;
		lst = lst->next;
	}
	return (first);
}
