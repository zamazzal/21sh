/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:27:25 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/13 17:36:17 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*backup;

	if (alst)
	{
		while (*alst)
		{
			backup = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = backup;
		}
	}
}
