/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:50:45 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:39:55 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void			ft_execbui(int rtn, int argc, char **argv)
{
	if (rtn == XECHO)
		ft_echo(argc, argv);
	else if (rtn == ENV)
		ft_env();
	else if (rtn == SETENV)
		ft_setinenv(argc, argv);
	else if (rtn == UNSETENV)
		ft_unsetenv(argv);
	else if (rtn == CD)
		ft_cd(argv);
	else if (rtn == TYPE)
		ft_type(argv[1]);
}

static void			ft_do_bui(char **argv, char *cmd, int rtn)
{
	int argc;

	if (!argv || !cmd)
		return ;
	argc = ft_tablen(argv);
	ft_execbui(rtn, argc, argv);
}

static void			ft_do_cbui(char **argv, char *cmd, int rtn, t_info info)
{
	int argc;
	int pid;

	if (!argv || !cmd)
		return ;
	argc = ft_tablen(argv);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (info.fd != -1)
			close(info.fd);
		ft_execbui(rtn, argc, argv);
		exit(0);
	}
}

int					ft_isbuiltin(char *cmd)
{
	if (ft_strequ(cmd, "echo"))
		return (XECHO);
	else if (ft_strequ(cmd, "cd"))
		return (CD);
	else if (ft_strequ(cmd, "setenv"))
		return (SETENV);
	else if (ft_strequ(cmd, "unsetenv"))
		return (UNSETENV);
	else if (ft_strequ(cmd, "env"))
		return (ENV);
	else if (ft_strequ(cmd, "exit"))
		return (EXIT);
	else if (ft_strequ(cmd, "type"))
		return (TYPE);
	return (0);
}

int					ft_builtins(char **argv, t_info info)
{
	char	*cmd;
	int		rtn;

	if (!argv)
		return (1);
	cmd = ft_strlwr(ft_strdup(argv[0]));
	rtn = ft_commands(argv, cmd, info.fd);
	if (rtn != 0 && rtn != 100)
	{
		if (rtn == EXIT)
		{
			ft_strdel(&cmd);
			return (0);
		}
		if (info.mode)
			ft_do_cbui(argv, cmd, rtn, info);
		else
			ft_do_bui(argv, cmd, rtn);
	}
	if (rtn == 100)
		ft_namerror(cmd);
	ft_strdel(&cmd);
	return (1);
}
