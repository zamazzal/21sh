/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:36:59 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 13:52:02 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (ft_strchr(s, c) == NULL)
		return (NULL);
	i = ft_strlen(s);
	while (s[i] != c)
		i--;
	return ((char*)s + i);
}
