/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:27:13 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:26:32 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_checkcmd(char *path)
{
	struct stat buf;

	if (!path)
	{
		ft_putendl(" : Bad address");
		return (0);
	}
	if (access(path, F_OK))
	{
		ft_cmderror(path);
		return (0);
	}
	if (access(path, X_OK))
	{
		ft_permerror(path);
		return (0);
	}
	lstat(path, &buf);
	if (!S_ISREG(buf.st_mode))
	{
		ft_putstr(path);
		ft_putendl(" : Not a Regular file");
		return (0);
	}
	return (1);
}

void			exec_cmd(char *exec, char **argv)
{
	int		r;
	pid_t	pid;

	r = 0;
	if (!ft_checkcmd(exec))
		return ;
	pid = fork();
	g_pid = 1;
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if ((r = execve(exec, argv, g_environ)) < 0)
			exit(EXIT_FAILURE);
	}
	wait(NULL);
}
