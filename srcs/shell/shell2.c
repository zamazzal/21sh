/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:01:37 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 15:22:40 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_checknoprint(int key, int pos)
{
	if (key == RIGHT)
	{
		if (pos + 1 < (int)ft_strlen(g_input))
			return (pos + 1);
	}
	if (key == LEFT)
	{
		return ((pos - 1 >= -1) ? (pos - 1) : -1);
	}
	if (key == BACKSPACE)
	{
		if (pos >= 0)
		{
			ft_strcpy(&g_input[pos], &g_input[pos + 1]);
			return ((pos - 1 >= -1) ? (pos - 1) : -1);
		}
	}
	return (pos);
}

char	*ft_prepareinput(void)
{
	char			*input;

	SAFE(input = ft_strnew(BUFFER_SIZE));
	ft_strclr(input);
	return (input);
}

void	ft_endinput(cmds, input)
	char **cmds;
	char *input;
	{
	ft_freetable(&cmds);
	ft_strdel(&input);
	}
