/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:23:38 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 15:37:36 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		rzlt;

	rzlt = 0;
	i = 0;
	while (rzlt == 0)
	{
		if (s1[i] != s2[i])
			rzlt = (unsigned char)s1[i] - (unsigned char)s2[i];
		else if ((s1[i] == '\0') && (s2[i] == '\0'))
			return (0);
		i++;
	}
	return (rzlt);
}
