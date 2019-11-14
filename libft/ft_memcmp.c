/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:08:51 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 13:27:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	x;

	x = 0;
	str1 = (char*)s1;
	str2 = (char*)s2;
	while (x < n)
	{
		if (str1[x] != str2[x])
			return ((unsigned char)str1[x] - (unsigned char)str2[x]);
		x++;
	}
	return (0);
}
