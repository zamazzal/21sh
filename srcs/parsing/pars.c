/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:24:41 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/22 21:41:23 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				checkbackslash(char *ptr, int i)
{
	int c;

	i--;
	c = 0;
	while (i >= 0)
	{
		if (ptr[i] == BS)
			c++;
		if (ptr[i] != BS)
			break ;
		i--;
	}
	return (c);
}

int				ft_getcindex(char *ptr, int c)
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
			return (i);
		i++;
	}
	return (-1);
}

int				ft_nbrofc(char *ptr, int c)
{
	int x;
	int nbr;

	nbr = 1;
	x = 0;
	while ((x = ft_getcindex(ptr, c)) != -1)
	{
		ptr += x + 1;
		if (x == 0)
			continue;
		if (*ptr == '\0')
			break ;
		nbr++;
	}
	return (nbr);
}

static char		**putcontent(char *ptr, int len, int c)
{
	int		i;
	int		x;
	int		chrlen;
	char	**cmds;

	i = 0;
	SAFE(cmds = (char **)malloc(sizeof(char *) * (len + 1)));
	while ((x = ft_getcindex(ptr, c)) != -1)
	{
		if (x != 0)
			cmds[i++] = ft_strsub(ptr, 0, x);
		ptr += x + 1;
	}
	chrlen = ft_strlen(ptr);
	if (chrlen > 0)
		cmds[i++] = ft_strsub(ptr, 0, chrlen);
	cmds[i] = NULL;
	return (cmds);
}

char			**ft_cmdsplit(char *ptr, int c)
{
	int len;

	len = ft_nbrofc(ptr, c);
	return (putcontent(ptr, len, c));
}
