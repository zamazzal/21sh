/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:38:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:42:55 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_puterror(char *error)
{
	ft_putstr_fd("mysh: ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}
