/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:47:52 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/22 21:39:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_tablen(char **array)
{
	int len;

	len = 0;
	if (!array)
		return (len);
	while (array[len] != NULL)
		len++;
	return (len);
}

void	ft_freetable(char ***array)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_tablen(*array);
	while (i < size)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	(*array) = NULL;
}

int		ft_strinstr(const char *s1, const char *s2, int len)
{
	int i;
	int j;

	if (!s1)
		return (0);
	if (s2[0] == '\0')
		return (1);
	i = 0;
	while ((s1[i] != '\0') && (i < len))
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i + j] != s2[j] || j + i >= len)
				break ;
			j++;
		}
		if (s2[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_lite(char *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(ptr = (char*)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (s1)
		ft_strdel(&s1);
	return (ptr);
}

char	*ft_strsub_lite(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || len <= 0 || (int)start < 0)
		return (NULL);
	if (!(ptr = (char*)malloc(len + 1)))
		return (NULL);
	while (i < len && s[start])
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	if (s)
		ft_strdel(&s);
	return (ptr);
}
