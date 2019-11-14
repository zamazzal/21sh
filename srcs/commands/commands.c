/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:22:42 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 15:24:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_isbuiltin(char *cmd)
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
	return (0);
}

static char		*ft_getcmd(char *cmd, char **paths)
{
	char			*real;
	DIR				*dir;
	int				i;
	struct dirent	*name;

	i = 0;
	real = NULL;
	while (paths[i] != NULL && !real)
	{
		dir = opendir(paths[i]);
		if (dir == NULL)
		{
			i++;
			continue;
		}
		while ((name = readdir(dir)) && !real)
		{
			if (ft_strequ(cmd, name->d_name))
				real = ft_strjoin_lite(ft_strjoin(paths[i], "/"), cmd);
		}
		closedir(dir);
		i++;
	}
	return (real);
}

static char		*ft_iscmd(char *cmd)
{
	char *path;
	char **paths;
	char *rzlt;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (!(path = ft_getenv("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	rzlt = ft_getcmd(cmd, paths);
	ft_freetable(&paths);
	return (rzlt);
}

int				ft_commands(char **argv, char *name, int fd)
{
	char	*exec;
	int		cmd;

	if ((cmd = ft_isbuiltin(name)))
		return (cmd);
	if ((exec = ft_iscmd(name)) == NULL)
		return (100);
	exec_cmd(exec, argv, fd);
	ft_strdel(&exec);
	return (0);
}
