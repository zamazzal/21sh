/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:51:16 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/27 21:35:13 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_term_canon(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_term_nocanon(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_term_echo(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_term_noecho(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_term_prepare(int mode)
{
	if (mode)
	{
		ft_term_canon();
	}
	else
	{
		ft_term_nocanon();
	}
}
