/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:53:00 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/14 14:17:19 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while ((haystack[i] != '\0') && (i < len))
	{
		j = 0;
		while (needle[j] != '\0')
		{
			if (haystack[i + j] != needle[j] || j + i >= len)
				break ;
			j++;
		}
		if (needle[j] == '\0')
			return ((char*)haystack + i);
		i++;
	}
	return (0);
}
