/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:22:02 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:26:16 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**removein(char **new, char *find, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_environ[i] != NULL)
	{
		if (!(ft_strinstr(g_environ[i], find, len)))
		{
			new[j] = ft_strdup(g_environ[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

static void		ft_removeenv(char *name)
{
	char	**tmp;
	char	**new;
	int		len;
	char	*find;

	len = ft_tablen(g_environ);
	if (!(new = (char **)malloc(sizeof(char *) * len)))
		return ;
	find = ft_strjoin(name, "=");
	len = ft_strlen(find);
	new = removein(new, find, len);
	tmp = g_environ;
	g_environ = new;
	ft_strdel(&find);
	ft_freetable(tmp);
}

void			ft_unsetenv(char **name)
{
	char	*env;
	int		i;

	i = 1;
	while (name[i] != NULL)
	{
		env = ft_getenv(name[i]);
		if (env != NULL)
			ft_removeenv(name[i]);
		i++;
	}
	if (i == 1)
		ft_putendl("usage : unsetenv [Name]");
}
