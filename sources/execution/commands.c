/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:22:42 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:39:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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

static int		ft_putin_htab(char *cmd, char *path)
{
	unsigned long	hash;
	t_hashtable		*tmp;

	if (!cmd)
		return (0);
	hash = ft_hash(cmd);
	tmp = g_htable[hash];
	while (g_htable[hash])
	{
		if (ft_strequ(g_htable[hash]->cmd, cmd))
			return (0);
		g_htable[hash] = g_htable[hash]->next;
	}
	SAFE(g_htable[hash] = (t_hashtable*)malloc(sizeof(t_hashtable)));
	g_htable[hash]->cmd = ft_strdup(cmd);
	g_htable[hash]->content = ft_strdup(path);
	g_htable[hash]->next = NULL;
	if (tmp)
		g_htable[hash] = tmp;
	return (0);
}

static char		*ft_getcmd_from_htab(char *cmd)
{
	unsigned long	hash;
	t_hashtable		*tmp;

	hash = ft_hash(cmd);
	tmp = g_htable[hash];
	while (tmp)
	{
		if (ft_strequ(tmp->cmd, cmd))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

char			*ft_iscmd(char *cmd)
{
	char *path;
	char **paths;
	char *rzlt;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if ((rzlt = ft_getcmd_from_htab(cmd)))
		return (rzlt);
	if (!(path = ft_getenv("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	rzlt = ft_getcmd(cmd, paths);
	ft_putin_htab(cmd, rzlt);
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
