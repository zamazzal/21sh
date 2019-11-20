/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:55:49 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/13 17:49:22 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int n)
{
	size_t	l;
	size_t	a;
	char	*ret;

	l = ft_nbrlen(n);
	if (!(ret = (char *)malloc(l + 1)))
		return (NULL);
	ret[l] = '\0';
	a = (n < 0) ? 1 : 0;
	if (a)
		ret[0] = '-';
	while (l > a)
	{
		l = l - 1;
		ret[l] = 48 + n % 10 * (n < 0 ? -1 : 1);
		n = n / 10;
	}
	return (ret);
}
