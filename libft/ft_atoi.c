/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:03:31 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/13 17:48:39 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		s;
	int		rzlt;
	size_t	i;

	i = 0;
	rzlt = 0;
	while (ft_isspace(str[i]))
		i++;
	s = str[i] == '-' ? -1 : 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		rzlt = rzlt + (str[i] - 48);
		if ((str[i + 1] >= '0') && (str[i + 1] <= '9'))
			rzlt = rzlt * 10;
		i++;
	}
	return (rzlt * s);
}
