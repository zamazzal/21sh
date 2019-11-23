/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:06:11 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:07:19 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_getnextpos(char *str, int pos)
{
	int i;

	i = pos;
	while (str[i] != '\0' && !ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && !ft_isspace(str[i]))
		return (i);
	return (-1);
}

void		ft_calcpos(t_cursor *cursor, int prompt, int *p)
{
	(*cursor).pos += ft_getlinelen((*cursor).y) - (*cursor).x;
	(*cursor).x = ((*cursor).y == 0) ? (*cursor).x + prompt : (*cursor).x;
	(*cursor).y++;
	*p = ft_getlinelen((*cursor).y);
	(*cursor).x = ((*cursor).x > *p) ? *p : (*cursor).x;
	(*cursor).pos += (*cursor).x + 1;
}

void		ft_endinput(char **cmds, char *input)
{
	ft_freetable(&cmds);
	ft_strdel(&input);
}
