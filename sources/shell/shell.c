/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:48:31 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:23:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		**ft_addtotab(char **tabl, char *str)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = ft_tablen(tabl) + 1;
	SAFE(new = (char **)malloc(sizeof(char*) * (len + 1)));
	while (tabl[i] != NULL)
	{
		new[i] = tabl[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[++i] = NULL;
	free(tabl);
	return (new);
}

static int	ft_shellexec(char **input, char ***history, char ***cmds)
{
	ft_strdel(&g_input);
	if (!(*input = makecmdclear(*input, *history)))
		return (1);
	ft_term_prepare(1);
	g_pars = -1;
	*history = ft_addtotab(*history, *input);
	if (!((*cmds = createcmds(*input))))
		return (1);
	g_pars = 0;
	if (ft_putcmds(*cmds, *history))
		return (2);
	ft_endinput(*cmds, *input);
	return (0);
}

void		ft_shell(void)
{
	char			*input;
	char			**cmds;
	char			**history;
	int				r;

	if (!(history = (char **)malloc(sizeof(char*))))
		return ;
	while (1)
	{
		ft_prompt(1);
		g_input_type = PROMPT;
		ft_term_prepare(0);
		if (!(input = ft_strdup(readline(history))) || parseerror(input, 1))
		{
			ft_strdel(&g_input);
			continue ;
		}
		r = ft_shellexec(&input, &history, &cmds);
		if (r == 1)
			continue ;
		else if (r == 2)
			break ;
	}
	ft_endinput(cmds, input);
	ft_freetable(&history);
}
