/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:48:54 by zamazzal          #+#    #+#             */
/*   Updated: 2019/10/17 16:48:56 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int ft_putterm(char *t)
{
    return (tputs(tgetstr(t, NULL), 1, ft_putchr));
}

int 	ft_getcurpos(void)
{
	int i;
	char str[32];

	i = 0;
	ft_putstr("\033[6n");
	read(1, &str[i], 2);
	while (i < 32)
	{
		read(1, &str[i], 1);
		if (str[i] == 'R')
			break ;
		i++;
	}
	str[i] = '\0';
	return (ft_atoi(str));
}

int 	ft_getcurpos2(void)
{
	int i;
	char str[32];

	i = 0;
	ft_term_prepare(0);
	ft_putstr("\033[6n");
	read(1, &str[i], 2);
	while (i < 32)
	{
		read(1, &str[i], 1);
		if (str[i] == 'R')
			break ;
		i++;
	}
	str[i] = '\0';
	ft_term_prepare(1);
	return (ft_atoi(ft_strchr(str, ';') + 1));
}