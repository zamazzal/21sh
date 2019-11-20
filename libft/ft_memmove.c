/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:40:24 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 17:12:28 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	x;
	char	back[len + 1];
	char	*s1;
	char	*s2;

	if (len > 65535)
		return (0);
	x = 0;
	s1 = (char*)src;
	s2 = (char *)dst;
	while (x < len)
	{
		back[x] = s1[x];
		x++;
	}
	x = 0;
	while (x < len)
	{
		s2[x] = back[x];
		x++;
	}
	return (dst);
}
