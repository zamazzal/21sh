/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:26:11 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 16:24:29 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

int		ft_checkcinstr(char *ptr, int c)
{
	int i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == DQ)
		{
			i++;
			while (ptr[i] && ptr[i] != DQ)
				i++;
		}
		if (ptr[i] == SQ)
		{
			i++;
			while (ptr[i] && ptr[i] != SQ)
				i++;
		}
		if (ptr[i] == c && !(checkbackslash(ptr, i) % 2))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strappend(char **a_s1, char c, int overwrite)
{
	char	*new;
	int		i;

	SAFE(new = (char *)malloc(sizeof(char) * (ft_strlen(*a_s1) + 2)));
	i = 0;
	while (*a_s1 && (*a_s1)[i])
	{
		new[i] = (*a_s1)[i];
		i++;
	}
	new[i] = c;
	new[++i] = '\0';
	if (overwrite == 1)
	{
		ft_strdel(a_s1);
		*a_s1 = new;
		return (NULL);
	}
	return (new);
}

int		quote_end(char *cmd, int start)
{
	int		i;
	char	quote;

	if (cmd[start] == SQ || cmd[start] == DQ || cmd[start] == BQ)
	{
		quote = cmd[start];
		i = start + 1;
		while (cmd[i] && cmd[i] != quote)
			i++;
		i++;
		return (i);
	}
	return (start);
}

char	*ft_strojoin(char **s1, char *s2, int overwrite)
{
	char	*tmp;

	if (overwrite)
	{
		tmp = ft_strjoin((const char *)(*s1), (const char *)s2);
		free(*s1);
		(*s1) = tmp;
		return (NULL);
	}
	return (ft_strjoin((const char *)(*s1), (const char *)s2));
}

void	ft_putintab(char ***a_chain, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;

	size = ft_tablen(*a_chain);
	new = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup((*a_chain)[i]);
		i++;
	}
	new[i] = ft_strdup(entry);
	i++;
	new[i] = NULL;
	ft_freetable(a_chain);
	*a_chain = new;
}
