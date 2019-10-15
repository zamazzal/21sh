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

int		ft_straddchr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i++] = c;
	str[i] = '\0';
	return (1);
}

int		ft_straddchrinpos(char c, int pos)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strdup(g_input);
	tmp2 = ft_strsub(tmp, 0, pos);
	ft_strclr(g_input);
	ft_strcpy(g_input, tmp2);
	ft_straddchr(g_input, c);
	ft_strcat(g_input, &tmp[pos]);
	free(tmp);
	free(tmp2);
	return (1);
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
