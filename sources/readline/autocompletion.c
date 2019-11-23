/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:57:35 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:28:56 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*iffinde(char *name, char *cmd, int *x, int *y)
{
	char *real;

	real = NULL;
	if (ft_strnstr(name, cmd, ft_strlen(cmd)))
	{
		if (*x == *y)
		{
			real = ft_strdup(name);
			(*x)++;
		}
		else
		{
			(*y)++;
		}
	}
	return (real);
}

static char	*ft_getinpath(char *cmd, char **paths, int *x)
{
	char			*real;
	DIR				*xdir;
	int				i;
	struct dirent	*name;
	int				y;

	i = 0;
	real = NULL;
	y = 0;
	while (paths[i] != NULL && !real)
	{
		xdir = opendir(paths[i]);
		if (xdir == NULL)
		{
			i++;
			continue;
		}
		while ((name = readdir(xdir)) && !real)
			real = iffinde(name->d_name, cmd, x, &y);
		closedir(xdir);
		i++;
	}
	if (paths[i] == NULL)
		(*x) = 0;
	return (real);
}

static char	*ft_getbultins(char *cmd)
{
	if (ft_strnstr("echo", cmd, ft_strlen(cmd)))
		return (ft_strdup("echo"));
	if (ft_strnstr("cd", cmd, ft_strlen(cmd)))
		return (ft_strdup("cd"));
	if (ft_strnstr("setenv", cmd, ft_strlen(cmd)))
		return (ft_strdup("setenv"));
	if (ft_strnstr("unsetenv", cmd, ft_strlen(cmd)))
		return (ft_strdup("unsetenv"));
	if (ft_strnstr("env", cmd, ft_strlen(cmd)))
		return (ft_strdup("env"));
	if (ft_strnstr("exit", cmd, ft_strlen(cmd)))
		return (ft_strdup("exit"));
	return (NULL);
}

static char	*ft_findcmd(char *cmd, int *i)
{
	char *path;
	char **paths;
	char *rzlt;

	rzlt = NULL;
	if ((rzlt = ft_getbultins(cmd)))
		return (rzlt);
	if (!(path = ft_getenv("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	rzlt = ft_getinpath(cmd, paths, i);
	ft_freetable(&paths);
	return (rzlt);
}

t_cursor	ft_autocompletion(t_cursor cursor)
{
	static int	i = 0;
	char		*cmd;

	if (!g_input && !g_autoc)
		return (cursor);
	ft_cpy();
	if (!g_autoc)
		g_autoc = ft_strdup(g_input);
	if (!(cmd = ft_findcmd(g_autoc, &i)))
		return (cursor);
	ft_strdel(&g_input);
	g_input = cmd;
	cursor = ft_defaultcursor(&cursor);
	cursor = ft_curright(cursor, ft_strlen(g_input));
	return (cursor);
}
