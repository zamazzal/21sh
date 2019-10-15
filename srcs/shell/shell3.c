/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:12:51 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 15:22:27 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	**createcmds(char *input)
{
	char	**cmds;

	SAFE(cmds = ft_cmdsplit(input, ';'));
	if (ft_checkcmds(cmds))
	{
		ft_strdel(&input);
		ft_freetable(&cmds);
		return (NULL);
	}
	return (cmds);
}
