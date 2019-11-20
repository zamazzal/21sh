/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   haashtable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:38:49 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:35:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

unsigned long	ft_hash(char *str)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (str[i] != '\0')
	{
		hash = ((hash << 5) + hash) + str[i];
		i++;
	}
	return (hash % HTABLE_SIZE);
}

void			ft_freeh_htab(void)
{
	int			i;
	t_hashtable	*tmp;

	i = 0;
	while (i <= HTABLE_SIZE)
	{
		if (g_htable[i])
		{
			while (g_htable[i])
			{
				tmp = g_htable[i];
				ft_strdel(&g_htable[i]->cmd);
				ft_strdel(&g_htable[i]->content);
				g_htable[i] = g_htable[i]->next;
				free(tmp);
			}
		}
		i++;
	}
}
