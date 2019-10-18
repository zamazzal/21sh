/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:43:54 by zamazzal          #+#    #+#             */
/*   Updated: 2019/10/18 16:47:51 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_cursleft(int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_putterm("le");
}

static void		ft_cursright(int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_putterm("nd");
}

static void		ft_cursup(int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_putterm("up");
}

static void		ft_cursdo(int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_putterm("do");
}

void			ft_cursmove(char c, int i)
{
	if (c == 'u')
		ft_cursup(i);
	if (c == 'd')
		ft_cursdo(i);
	if (c == 'r')
		ft_cursright(i);
	if (c == 'l')
		ft_cursleft(i);
}
