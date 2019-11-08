/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:44:34 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/08 21:44:44 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_ctrld(int pos)
{
	if (*g_input == '\0')
		return (1);
	ft_strcpy(&g_input[pos], &g_input[pos + 1]);
	return (0);
}

int			doctrld(int key)
{
	if (key == CTRLD)
	{
		if (ft_ctrld(g_cursor.pos))
			return (1);
	}
	return (0);
}
