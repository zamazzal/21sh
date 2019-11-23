/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:56:49 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 16:01:46 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		close_toclose(t_to_close **head)
{
	t_to_close	*curr;
	t_to_close	*next;

	curr = *head;
	while (curr)
	{
		close(curr->fd);
		curr = curr->next;
	}
	curr = *head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void		append_toclose(t_to_close **head, int fd)
{
	t_to_close	*curr;

	curr = *head;
	if (*head == NULL)
	{
		if (!((*head) = (t_to_close *)malloc(sizeof(t_to_close))))
			return ;
		(*head)->fd = fd;
		(*head)->next = NULL;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		if ((!(curr->next = (t_to_close *)malloc(sizeof(t_to_close)))))
			return ;
		curr->next->fd = fd;
		curr->next->next = NULL;
	}
}
