/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:50:45 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:14:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_do_bui(char **argv, char *cmd, int rtn)
{
	int argc;

	if (!argv || !cmd)
		return ;
	argc = ft_tablen(argv);
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
}

void		ft_do_cbui(char **argv, char *cmd, int rtn, t_info info)
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
		exit(0);
	}
}

int				ft_builtins(char **argv, t_info info)
{
	char	*cmd;
	int		rtn;

	if (!argv)
		return (1);
	cmd = ft_strdup(argv[0]);
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
	{
		ft_namerror(cmd);
	}
	ft_strdel(&cmd);
	return (1);
}
