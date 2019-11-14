/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:42:28 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:24:10 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_env(void)
{
	ft_puttables(g_environ);
}

char			*ft_getenv(const char *name)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	if (!name)
		return (NULL);
	env = ft_strjoin(name, "=");
	len = ft_strlen(env);
	while (g_environ[i] != NULL)
	{
		if (ft_strinstr(g_environ[i], env, len))
		{
			ft_strdel(&env);
			return (ft_strchr(g_environ[i], '=') + 1);
		}
		i++;
	}
	ft_strdel(&env);
	return (NULL);
}
