/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 21:35:05 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/13 17:33:27 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*backup;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->next = NULL;
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
		return (new);
	}
	if (!(backup = (t_list*)malloc(content_size)))
		return (NULL);
	backup = ft_memcpy(backup, content, content_size);
	if (backup)
	{
		new->content = backup;
		new->content_size = content_size;
		return (new);
	}
	return (NULL);
}
