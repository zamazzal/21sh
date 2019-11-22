/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:11:24 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 18:49:35 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

struct winsize	ft_winsize(void)
{
	struct winsize ts;

	ioctl(0, TIOCGWINSZ, &ts);
	ts.ws_col--;
	return (ts);
}

void			ft_putnstr(char *str, int n)
{
	while (n > 0)
	{
		ft_putstr(str);
		n--;
	}
}
