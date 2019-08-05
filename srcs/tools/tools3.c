/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:36:59 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/22 16:37:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		ft_count_words(const char *str, char c, char x)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == c || str[i] == x) && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static	char	*ft_word(const char *str, char c, char x, int *i)
{
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while ((str[*i] != c && str[*i] != x) && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while ((str[*i] == c || str[*i] == x) && str[*i])
		*i += 1;
	return (s);
}

char			**ft_strsplit_d(const char *str, char c, char x)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	wrd = ft_count_words(str, c, x);
	if (!(s = (char **)malloc(sizeof(s) * (wrd + 2))))
		return (NULL);
	while ((str[i] == c || str[i] == x) && str[i])
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, c, x, &i);
		j++;
	}
	s[j] = NULL;
	return (s);
}
