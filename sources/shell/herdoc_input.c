/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:29:27 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:46:36 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			**herdocreturn(int i, int *status, char **herdoc)
{
	if (i == 1)
	{
		*status = 1;
		ft_freetable(&herdoc);
		return (NULL);
	}
	ft_strdel(&g_input);
	return (herdoc);
}

static char			**putherdoc(char *str, char **history, int *status)
{
	char	**herdoc;
	int		i;

	SAFE(herdoc = (char **)malloc(sizeof(char *)));
	herdoc[0] = NULL;
	i = 0;
	ft_term_prepare(0);
	while (1337)
	{
		g_cursor = ft_defaultcursor(&g_cursor);
		ft_putterm("cr");
		ft_putstr("heredoc> ");
		g_input_type = HERDOC;
		g_input = readline5(history, &i);
		if (i == 1 || i == 2 || ft_strequ(g_input, str))
			break ;
		herdoc = ft_addtotab(herdoc, g_input);
		ft_strdel(&g_input);
	}
	ft_term_prepare(1);
	return (herdocreturn(i, status, herdoc));
}

static char			**ft_getherd_content(char *cmd, char **history, int *status)
{
	char **herdoc;
	char *ptr;
	char *str;

	herdoc = NULL;
	ptr = cmd;
	while ((ptr = ft_strstr(ptr, "<<")))
	{
		ptr = ptr + 2;
		str = get_herdoc_right(ptr);
		if (herdoc)
			ft_freetable(&herdoc);
		herdoc = putherdoc(str, history, status);
		ft_strdel(&str);
		if (*status)
			break ;
	}
	return (herdoc);
}

static t_semiherdoc	*ft_semiherdoc(char *cmd, char **history, int *status)
{
	int				i;
	t_semiherdoc	*sherdoc;
	t_semiherdoc	*head;
	char			**sub;

	i = 0;
	SAFE(sub = ft_cmdsplit(cmd, '|'));
	SAFE(sherdoc = (t_semiherdoc*)malloc(sizeof(t_semiherdoc)));
	head = sherdoc;
	while (sub[i] != NULL)
	{
		sherdoc->content = ft_getherd_content(sub[i], history, status);
		if (*status)
			break ;
		if (sub[i + 1] != NULL)
		{
			SAFE(sherdoc->next = (t_semiherdoc*)malloc(sizeof(t_semiherdoc)));
			sherdoc = sherdoc->next;
		}
		i++;
	}
	ft_freetable(&sub);
	sherdoc->next = NULL;
	return (head);
}

t_herdoc			*ft_herdoc(char **cmds, char **history, int *status)
{
	t_herdoc	*herdoc;
	t_herdoc	*head;
	int			len;
	int			i;

	len = ft_tablen(cmds);
	if (!(herdoc = (t_herdoc*)malloc(sizeof(t_herdoc))))
		return (NULL);
	i = 0;
	head = herdoc;
	while (cmds[i] != NULL)
	{
		herdoc->semiherdoc = ft_semiherdoc(cmds[i], history, status);
		if (*status)
			break ;
		if (cmds[i + 1] != NULL)
		{
			SAFE(herdoc->next = (t_herdoc*)malloc(sizeof(t_herdoc)));
			herdoc = herdoc->next;
		}
		i++;
	}
	herdoc->next = NULL;
	return (head);
}
