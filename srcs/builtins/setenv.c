/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:27:26 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:25:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		addenv(char *env, int len)
{
	char	**tmp;
	int		i;
	char	**new;

	if (!(new = (char **)malloc(sizeof(char*) * (len + 2))))
	{
		ft_putendl("memory allocation : error");
		return ;
	}
	new[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(g_environ[i]);
		i++;
	}
	new[i++] = env;
	tmp = g_environ;
	g_environ = new;
	ft_freetable(tmp);
}

static int		setinenv(char *env, char *find)
{
	int		findlen;
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	len = 0;
	findlen = ft_strlen(find);
	while (g_environ[i] != NULL)
	{
		if (ft_strinstr(g_environ[i], find, findlen))
		{
			tmp = g_environ[i];
			g_environ[i] = env;
			ft_strdel(&tmp);
			return (0);
		}
		i++;
		len++;
	}
	return (len);
}

void			ft_setenv(char *name, char *content)
{
	int		len;
	char	*env;
	char	*find;

	find = ft_strjoin(name, "=");
	env = ft_strjoin(find, content);
	if ((len = setinenv(env, find)) == 0)
	{
		ft_strdel(&find);
		return ;
	}
	ft_strdel(&find);
	addenv(env, len);
}

void			ft_setinenv(int argc, char **argv)
{
	if (argc != 3 || !argv[1] || !argv[2])
	{
		ft_putendl("usage : setenv [Name] [Content]");
		return ;
	}
	ft_setenv(argv[1], argv[2]);
}
