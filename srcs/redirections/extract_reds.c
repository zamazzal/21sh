/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_reds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:01:23 by aihya             #+#    #+#             */
/*   Updated: 2019/11/17 17:33:27 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"


t_red *red_node(t_pos_tab *pos_tab_node, char **wings)
{
	t_red *node;

	node = (t_red *)malloc(sizeof(t_red));
	node->type = pos_tab_node->type;
	node->right = ft_strdup(wings[0]);
	node->left = ft_strdup(wings[1]);
	node->next = NULL;
	return (node);
}

void set_pos_table(t_pos_tab **pos_tab, int pos, int red_type)
{
	int	i;
	t_pos_tab	*curr;

	i = 0;
	curr = *pos_tab;
	if (curr == NULL)
	{
		(*pos_tab) = (t_pos_tab *)malloc(sizeof(t_pos_tab));
		(*pos_tab)->pos = pos;
		(*pos_tab)->type = red_type;
		(*pos_tab)->next = NULL;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = (t_pos_tab *)malloc(sizeof(t_pos_tab));
		curr->next->pos = pos;
		curr->next->type = red_type;
		curr->next->next = NULL;
	}
}

void append_red_node(t_red **a_head, t_red *node)
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

int append_red_symbol(t_pos_tab **pos_tab, char *cmd, int i)
{
	int k;
	char sym;

	sym = cmd[i];
	k = count_red(cmd, i, 1);
	if (k == 1)
		set_pos_table(pos_tab, i, (sym == '>' ? RS : LS));
	else if (k == 2)
		set_pos_table(pos_tab, i, (sym == '>' ? RD : LD));
	return (k);
}

t_pos_tab	*get_reds_positions(char *cmd)
{
	int			i;
	t_pos_tab	*pos_tab;

	pos_tab = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			i = quote_end(cmd, i);
			continue;
		}
		else if (ft_strchr("><", cmd[i]))
		{
			i += append_red_symbol(&pos_tab, cmd, i);
			continue;
		}
		i++;
	}

	return (pos_tab);
}

char *get_right(char *cmd, int pos, int steps)
{
	int i;
	char *right;
	char q;

	right = NULL;
	i = pos + steps;
	while (cmd[i] && cmd[i] == ' ')
		ft_strappend(&right, cmd[i++], 1);
	while (cmd[i] && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(&right, cmd[i++], 1);
		if (cmd[i - 1] && ft_strchr("\"\'", cmd[i - 1]))
		{
			q = cmd[i - 1];
			while (cmd[i] != q)
				ft_strappend(&right, cmd[i++], 1);
			ft_strappend(&right, cmd[i++], 1);
		}
	}
	
	if (ft_strlen(right) == 1 && right[0] == '&')
	{
		while (cmd[i] && cmd[i] == ' ')
			ft_strappend(&right, cmd[i++], 1);
		while (cmd[i] && !ft_strchr("> <", cmd[i]))
		{
			ft_strappend(&right, cmd[i++], 1);
			if (ft_strchr("\"\'", cmd[i - 1]))
			{
				q = cmd[i - 1];
				while (cmd[i] != q)
					ft_strappend(&right, cmd[i++], 1);
				ft_strappend(&right, cmd[i++], 1);
			}
		}
	}
	return (right);
}

char *get_left(char *cmd, int pos)
{
	int i;
	char *left;
	char *tmp;
	char q;

	left = NULL;
	tmp = NULL;
	i = pos - 1;
	while (i >= 0 && cmd[i] == ' ')
		ft_strappend(&left, cmd[i--], 1);
	while (i >= 0 && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(&left, cmd[i--], 1);
		if (ft_strchr("\"\'", cmd[i + 1]))
		{
			q = cmd[i + 1];
			while (cmd[i] != q)
				ft_strappend(&left, cmd[i--], 1);
			ft_strappend(&left, cmd[i--], 1);
		}
	}
	if (left != NULL)
	{
		tmp = ft_strrev(left);
		free(left);
		left = ft_strdup(tmp);
		free(tmp);
	}
	return (left);
}

char **get_red_wings(char *cmd, t_pos_tab *node)
{
	char **wings;

	wings = (char **)malloc(sizeof(char *) * 3);
	if (node->type == LS || node->type == RS)
	{
		wings[0] = get_right(cmd, node->pos, 1);
		wings[1] = get_left(cmd, node->pos);
	}
	else if (node->type == LD || node->type == RD)
	{
		wings[0] = get_right(cmd, node->pos, 2);
		wings[1] = get_left(cmd, node->pos);
	}
	wings[2] = NULL;
	return (wings);
}

void	free_pos_tab(t_pos_tab **pos_tab)
{
	t_pos_tab	*curr;
	t_pos_tab	*next;

	curr = *pos_tab;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*pos_tab = NULL;
}

t_red *extract_reds(char *cmd)
{
	t_red *head;
	t_red *node;
	char **wings;
	t_pos_tab *reds_pos;
	t_pos_tab *curr;

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
