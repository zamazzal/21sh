/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_reds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:01:23 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 18:50:35 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static t_red	*red_node(t_pos_tab *pos_tab_node, char **wings)
{
	t_red *node;

	node = (t_red *)malloc(sizeof(t_red));
	node->type = pos_tab_node->type;
	node->right = ft_strdup(wings[0]);
	node->left = ft_strdup(wings[1]);
	node->next = NULL;
	return (node);
}

static void		append_red_node(t_red **a_head, t_red *node)
{
	t_red *curr;

	if (*a_head == NULL)
		*a_head = node;
	else
	{
		curr = *a_head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

t_red			*extract_reds(char *cmd)
{
	t_red		*head;
	t_red		*node;
	char		**wings;
	t_pos_tab	*reds_pos;
	t_pos_tab	*curr;

	head = NULL;
	reds_pos = get_reds_positions(cmd);
	if (reds_pos != NULL)
	{
		curr = reds_pos;
		while (curr != NULL)
		{
			wings = get_red_wings(cmd, curr);
			node = red_node(curr, wings);
			node->pos = curr->pos;
			append_red_node(&head, node);
			ft_freetable(&wings);
			curr = curr->next;
		}
	}
	free_pos_tab(&reds_pos);
	return (head);
}
