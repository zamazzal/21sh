/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:48:33 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/12 11:49:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int doublesemicol(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == ';')
		{
			if (cmd[i + 1] && cmd[i + 1] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

static int doublepipe(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|')
		{
			if (cmd[i + 1] && cmd[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

static int pipeandsemicol(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == ';')
		{
			if (cmd[i + 1] && cmd[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int parseerror(char *cmd)
{
	if (doublesemicol(cmd))
		ft_putendl_fd("21sh : parse error near `;;'", 2);
	if (doublepipe(cmd))
		ft_putendl_fd("21sh : parse error near `||'", 2);
	if (pipeandsemicol(cmd))
		ft_putendl_fd("21sh : parse error near `;|'", 2);
	else
		return (0);
	return (1);
}

