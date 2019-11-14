/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:45:59 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/14 18:46:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char const *s)
{
	char	*s_rev;
	int		i;

	if (!s || !(s_rev = (char *)malloc(sizeof(char) * ((int)ft_strlen(s) + 1))))
		return (NULL);
	i = (int)ft_strlen(s);
	while (i)
	{
		s_rev[(int)ft_strlen(s) - i] = s[i - 1];
		i--;
	}
	s_rev[ft_strlen(s)] = '\0';
	return (s_rev);
}
