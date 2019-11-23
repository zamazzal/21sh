/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:23:39 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 13:50:01 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		x;
	char		f;

	x = 0;
	f = (char)c;
	while (s[x])
	{
		if (s[x] == f)
			return ((char*)s + x);
		x++;
	}
	if (s[x] == f)
		return ((char*)s + x);
	return (NULL);
}
