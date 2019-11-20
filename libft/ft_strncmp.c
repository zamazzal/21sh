/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:50:16 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 19:06:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		rzlt;

	rzlt = 0;
	i = 0;
	while ((rzlt == 0 && i < n))
	{
		if (s1[i] != s2[i])
			rzlt = (unsigned char)s1[i] - (unsigned char)s2[i];
		else if ((s1[i] == '\0') && (s2[i] == '\0'))
			return (0);
		i++;
	}
	if (s1[i] != '\0')
		return (rzlt);
	return (1);
}
