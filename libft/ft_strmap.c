/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 00:02:13 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 17:04:58 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t		i;
	size_t		l;
	char		*ptr;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	if (!(ptr = (char *)malloc(l + 1)))
		return (NULL);
	i = 0;
	while (i < l)
	{
		ptr[i] = f(s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
