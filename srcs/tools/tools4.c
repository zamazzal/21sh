/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:26:11 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/05 21:16:31 by zamazzal         ###   ########.fr       */
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
