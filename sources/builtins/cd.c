/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 19:48:38 by zamazzal          #+#    #+#             */
/*   Updated: 2019/12/08 18:16:00 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_checkaccess(char *path, char *name)
{
	struct stat buf;

	if (access(path, F_OK))
	{
		ft_putstr("cd: ");
		ft_cmderror(name);
		return (0);
	}
	if (access(path, X_OK))
	{
		ft_putstr("cd: ");
		ft_permerror(name);
		return (0);
	}
	lstat(path, &buf);
	if (!(buf.st_mode & 0040000) && !(buf.st_mode & 0120000))
	{
		ft_putstr("cd: ");
		ft_notdir(name);
		return (0);
	}
	return (1);
}

static void		ft_entre(char *path, char *name)
{
	char *now;

	if (ft_checkaccess(path, name))
	{
		if (chdir(path) == -1)
		{
			ft_putendl("cd : error");
			return ;
		}
		now = getcwd(ft_strnew(1023 + ft_strlen(path) + 1), BUFFER_SIZE);
		ft_setenv("PWD", now);
		ft_strdel(&now);
	}
}

static void		ft_goback(char *path)
{
	char *now;
	char *old;

	now = ft_strdup(ft_getenv("OLDPWD"));
	if (now == NULL)
	{
		ft_putendl("cd error : OLDPATH is NULL");
		return ;
	}
	old = getcwd(ft_strnew(1023), BUFFER_SIZE);
	ft_setenv("OLDPWD", old);
	ft_entre(now, now);
	ft_strdel(&now);
	extra_free(old, path);
}

static	char	*ft_getpath(char *str)
{
	char *path;

	path = (!str || ft_strequ(str, "--")) ?
	ft_strdup(ft_getenv("HOME")) : ft_strdup(str);
	return (path);
}

void			ft_cd(char **argv)
{
	char *path;
	char *old;
	char *now;

	if (!(path = ft_getpath(argv[1])))
		return ;
	if (ft_strequ(path, "-"))
	{
		ft_goback(path);
		return ;
	}
	old = getcwd(ft_strnew(1023), BUFFER_SIZE);
	ft_setenv("OLDPWD", old);
	ft_strdel(&old);
	if (path[0] != '/' && path[0] != '.' && path[0] != '-')
	{
		now = getcwd(ft_strnew(1023 + ft_strlen(path) + 1), BUFFER_SIZE);
		now = ft_strjoin_lite(ft_strjoin_lite(now, "/"), path);
		ft_entre(now, path);
		extra_free(now, path);
		return ;
	}
	ft_entre(path, path);
	ft_strdel(&path);
}
