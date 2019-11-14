/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:45:08 by zamazzal          #+#    #+#             */
/*   Updated: 2018/10/11 16:42:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = (char*)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strncpy(ptr, "\0", size + 1);
	return (ptr);
}
