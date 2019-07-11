/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:24:46 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/12 14:14:38 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s)
		return (NULL);
	start = 0;
	while (ft_isspace(s[start]))
		start++;
	end = ft_strlen(s) - 1;
	while (start < end && ft_isspace(s[end]))
		end--;
	ptr = ft_strsub(s, start, end - start + 1);
	return (ptr);
}
