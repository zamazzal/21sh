/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:54:12 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/05 21:17:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		count_red(char *cmd, int start, int same)
{
	int		i;
	int		c;

	c = 0;
	i = start;
	if (same)
	{
		while (cmd[i] && cmd[start] == cmd[i])
		{
			i++;
			c++;
		}
	}
	else
	{
		while (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		{
			i++;
			c++;
		}
	}
	return (c);
}

static int		check_counted_red(int c, int lim, char *cmd, int curr)
{
	char	*tmp;

	tmp = ft_strdup("parse error near ");
	if (c > lim)
	{
		ft_strappend(&tmp, cmd[curr], 1);
		ft_strappend(&tmp, cmd[curr + 1], 1);
		ft_puterror(tmp);
		ft_strdel(&tmp);
		return (0);
	}
	else if (lim - 1 == 0 || c > lim - 1)
	{
		ft_strappend(&tmp, cmd[curr], 1);
		ft_puterror(tmp);
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

static int		ft_redputerror(char *cmd, int i, int c, int end)
{
	int		j;

	j = i + c;
	while (cmd[j] && cmd[j] == ' ')
		j++;
	if (!cmd[j])
	{
		if (end == 0)
			ft_puterror("parse error near `\\n'");
		else if (end == 1)
			ft_puterror("parse error near `;'");
		else if (end == 2)
			ft_puterror("parse error near `|'");
		return (0);
	}
	else if (cmd[j] && (cmd[j] == '>' || cmd[j] == '<'))
		return (check_counted_red(count_red(cmd, j, 0), 1, cmd, j));
	return (c);
}

int				check_reds(char *cmd, int end)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	while (cmd[i])
	{
		i = quote_end(cmd, i);
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			c = count_red(cmd, i, 1);
			if (check_counted_red(c, 3, cmd, i) == 1)
			{
				j = i + c;
				if (ft_redputerror(cmd, i, c, end) == 0)
					return (0);
				i += c - 1;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}
