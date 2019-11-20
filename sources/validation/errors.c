/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:48:33 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/27 21:34:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	doublesemicol(char *cmd)
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

static int	doublepipe(char *cmd)
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

static int	pipeandsemicol(char *cmd)
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

static int	pipeinfirst(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != '|' && cmd[i] != ' ')
			return (0);
		if (cmd[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int			parseerror(char *cmd, int mode)
{
	if (mode == 1)
	{
		if (doublesemicol(cmd))
			ft_puterror("parse error near `;;'");
		else if (doublepipe(cmd))
			ft_puterror("parse error near `||'");
		else if (pipeandsemicol(cmd))
			ft_puterror("parse error near `;|'");
		else if (pipeinfirst(cmd))
			ft_puterror("parse error near `|'");
		if (ft_redirerror(cmd))
			return (1);
		else
			return (0);
		return (1);
	}
	if (pipeinfirst(cmd))
		ft_puterror("parse error near `|'");
	else
		return (0);
	return (1);
}
