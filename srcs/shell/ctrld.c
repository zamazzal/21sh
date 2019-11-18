/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:44:34 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 16:58:04 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_ctrld2(int pos)
{
	if (!g_input)
		return (0);
	ft_strcpy(&g_input[pos], &g_input[pos + 1]);
	if (*g_input == '\0')
		ft_strdel(&g_input);
	return (0);
}

static int		ft_ctrld(int pos)
{
	if (!g_input)
	{
		g_input = ft_strdup("exit");
		return (1);
	}
	ft_strcpy(&g_input[pos], &g_input[pos + 1]);
	if (*g_input == '\0')
		ft_strdel(&g_input);
	return (0);
}

int				doctrld(int key, int mode)
{
	if (key == CTRLD)
	{
		ft_cpy();
		if (mode)
		{
			if (ft_ctrld(g_cursor.pos))
				return (1);
		}
		else
		{
			ft_ctrld2(g_cursor.pos);
		}
	}
	return (0);
}
