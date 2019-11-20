/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:58:55 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/22 16:34:04 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	if (s1)
	{
		if (!(dest = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
			return (NULL);
		ft_strcpy(dest, s1);
		return (dest);
	}
	return (NULL);
}
