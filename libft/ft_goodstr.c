/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goodstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:38:19 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/12 14:15:01 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_goodstr(char *str)
{
	size_t x;

	x = 0;
	while (str[x] != '\0')
	{
		if (ft_isalnum(str[x - 1]))
		{
			if (str[x] >= 'A' && str[x] <= 'Z')
				str[x] = ft_tolower(str[x]);
		}
		else
		{
			if (str[x] >= 'a' && str[x] <= 'z')
				str[x] = ft_toupper(str[x]);
		}
		x++;
	}
	return (str);
}
