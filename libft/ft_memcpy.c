/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:01:30 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/14 15:08:39 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	x;
	char	*str;
	char	*ptr;

	x = 0;
	str = (char*)src;
	ptr = (char*)dst;
	while (x < n)
	{
		ptr[x] = str[x];
		x++;
	}
	return (dst);
}
