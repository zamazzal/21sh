/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:46:12 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/14 14:14:42 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		destl;
	size_t		srcl;
	size_t		rzlt;
	size_t		x;

	rzlt = 0;
	destl = ft_strlen(dst);
	srcl = ft_strlen(src);
	x = 0;
	rzlt = (size < destl) ? srcl + size : srcl + destl;
	while (src[x] && destl + 1 < size)
		dst[destl++] = src[x++];
	dst[destl] = '\0';
	return (rzlt);
}
