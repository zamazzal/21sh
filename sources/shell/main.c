/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 21:25:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**creation(char **table)
{
	char	**new;

	g_pid = 0;
	new = ft_tabdup(table);
	return (new);
}

int				main(void)
{
	extern char		**environ;

	if (ft_tinit() == -1 || ft_checktitty())
		return (0);
	signal(SIGINT, ft_signal);
	SAFE(g_environ = creation(environ));
	ft_memset(g_htable, 0, HTABLE_SIZE);
	g_pars = 0;
	g_input_type = 0;
	ft_shell();
	ft_freeh_htab();
	ft_freetable(&g_environ);
	return (1);
}
