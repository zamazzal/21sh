/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:49:29 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:30:35 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_strisprint(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] >= 33 && str[i] <= 126)
				return (1);
			i++;
		}
	}
	return (0);
}

static int		ft_inputerror(char *input, int mode)
{
	if (parseerror(input, mode))
		return (1);
	if (!ft_strisprint(input))
		return (1);
	return (0);
}

int				ft_checkcmds(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_inputerror(array[i], 2))
			return (1);
		i++;
	}
	return (0);
}
