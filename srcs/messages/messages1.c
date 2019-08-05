/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:38:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/27 21:36:41 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_putnstr(char *str, int n)
{
	while (n > 0)
	{
		ft_putstr(str);
		n--;
	}
}

void	ft_puterror(char *error)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(error, 2);
}
