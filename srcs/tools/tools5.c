/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:38:49 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 19:41:00 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

unsigned long ft_hash(char *str)
{
	int i;
	unsigned long hash = 5381;

	i = 0;
	while (str[i] != '\0')
	{
		hash = ((hash << 5) + hash) + str[i];
		i++;
	}
	return (hash % HTABLE_SIZE);
}

void			ft_freeh_htab()
{
	int i;
	t_hashtable *tmp;

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