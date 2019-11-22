/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:31:28 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:45:48 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*get_herdoc_right(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
		i++;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t'))
		i++;
	new = ms_get_arg(&str[i]);
	tmp = new;
	new = ms_expand_quotes(new);
	ft_strdel(&tmp);
	return (new);
}

int		ft_freeherdoc(t_herdoc *herdoc)
{
	t_herdoc		*back1;
	t_semiherdoc	*back2;
	t_semiherdoc	*tmp;

	while (herdoc)
	{
		tmp = herdoc->semiherdoc;
		while (tmp)
		{
			back2 = tmp;
			tmp = tmp->next;
			free(back2);
		}
		back1 = herdoc;
		herdoc = herdoc->next;
		free(back1);
	}
	return (0);
}
