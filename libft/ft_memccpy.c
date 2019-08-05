/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:15:23 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/14 15:09:26 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			x;
	unsigned char	*str;
	unsigned char	*ptr;

	x = 0;
	str = (unsigned char*)src;
	ptr = (unsigned char*)dst;
	while (x < n)
	{
		if (str[x] == (unsigned char)c)
		{
			ptr[x] = str[x];
			return (dst + (x + 1));
		}
		ptr[x] = str[x];
		x++;
	}
	return (NULL);
}
