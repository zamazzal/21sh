/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 21:08:11 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/07 13:14:41 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_tinit(void)
{
	char	*term;
	int		r;

	term = getenv("TERM");
	if (term == NULL)
	{
		ft_puterror("TERM must be set (see 'env').");
		return (-1);
	}
	r = tgetent(NULL, term);
	if (r == -1)
	{
		ft_puterror("Could not access to the termcap database..");
		return (-1);
	}
	if (r == 0)
	{
		ft_puterror("this Terminal is not defined in termcap database.");
		return (-1);
	}
	return (r);
}

int		ft_checktitty(void)
{
	if (!isatty(0))
	{
		ft_puterror("You are not in terminal");
		return (1);
	}
	return (0);
}
