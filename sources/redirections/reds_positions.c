/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reds_positions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:07:38 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 18:51:46 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		set_pos_table(t_pos_tab **pos_tab, int pos, int red_type)
{
	int			i;
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

static int		append_red_symbol(t_pos_tab **pos_tab, char *cmd, int i)
{
	int		k;
	char	sym;

	sym = cmd[i];
	k = count_red(cmd, i, 1);
	if (k == 1)
		set_pos_table(pos_tab, i, (sym == '>' ? RS : LS));
	else if (k == 2)
		set_pos_table(pos_tab, i, (sym == '>' ? RD : LD));
	return (k);
}

void			free_pos_tab(t_pos_tab **pos_tab)
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

t_pos_tab		*get_reds_positions(char *cmd)
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
