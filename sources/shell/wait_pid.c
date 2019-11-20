/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:41:18 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:47:52 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_backline(void)
{
	int x;

	x = ft_getcurpos2();
	if (x > 1)
	{
		ft_putterm("mr");
		ft_putchar('%');
		ft_putterm("me");
		ft_putchar(' ');
		ft_putchar('\n');
	}
}

void			ft_waitpids(void)
{
	int r;
	int x;

	r = wait(NULL);
	x = 0;
	while (r > 0)
	{
		x++;
		r = wait(NULL);
	}
	if (x)
		ft_backline();
}
