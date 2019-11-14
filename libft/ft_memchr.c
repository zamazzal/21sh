/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:52:24 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/14 15:08:56 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*ptr;

	x = 0;
	ptr = (unsigned char*)s;
	while (x < n)
	{
		if (ptr[x] == (unsigned char)c)
			return ((unsigned char*)s + x);
		x++;
	}
	return (0);
}
