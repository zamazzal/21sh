/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:41:50 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:47:29 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	**ctables(char **array)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			len = ft_strlen(array[i]);
			if (array[i][0] == SQ && array[i][len - 1] == SQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == DQ && array[i][len - 1] == DQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == BQ && array[i][len - 1] == BQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			i++;
		}
		return (array);
	}
	return (NULL);
}

int			putcmd(char *cmd, char **cmds, t_info info, t_to_close **toclose)
{
	char **argv;

	argv = ms_parse(cmd);
	if (!(ft_builtins(ctables(argv), info)))
	{
		ft_strdel(&cmd);
		ft_freetable(&cmds);
		ft_freetable(&argv);
		close_toclose(toclose);
		return (1);
	}
	ft_freetable(&argv);
	return (0);
}
