/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:38:55 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 15:22:04 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_straddchr(char *str, char c)
{
	char *new;
	int i;
	int len;

	len = ft_strlen(str);
	new = ft_strnew(len + 1);
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	ft_strdel(&str);
	return (new);
}

void	double_free(char *dead1, char **dead2)
{
	if (dead1)
		ft_strdel(&dead1);
	if (*dead2)
		ft_freetable(&dead2);
}

void	extra_free(char *dead1, char *dead2)
{
	if (dead1)
		ft_strdel(&dead1);
	if (dead2)
		ft_strdel(&dead2);
}

int		ft_checkc(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
