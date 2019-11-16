/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:17:35 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 16:24:52 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*ms_quote_content(char *str)
{
	int		i;
	char	quote;
	char	*content;

	i = 0;
	quote = str[0];
	content = ft_strnew(0);
	while (str[i])
	{
		if (str[i] == quote && i != 0)
			break ;
		ft_strappend(&content, str[i], TRUE);
		i++;
	}
	return (content);
}

static char	**ms_expand_args(char **args)
{
	char	**buffer;
	char	*tmp;
	int		i;

	tmp = NULL;
	buffer = NULL;
	i = 0;
	while (args[i])
	{
		tmp = ms_expand_arg(args[i]);
		ft_putintab(&buffer, tmp);
		ft_strdel(&tmp);
		i++;
	}
	return (buffer);
}

char	*ms_get_arg(char *line)
{
	int		i;
	char	*arg;
	char	*quote_content;

	i = 0;
	arg = ft_strnew(0);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			break ;
		if (line[i] == DQ || line[i] == SQ)
		{
			quote_content = ms_quote_content(line + i);
			ft_strojoin(&arg, quote_content, TRUE);
			i = i + ft_strlen(quote_content);
			ft_strdel(&quote_content);
			ft_strappend(&arg, line[i], TRUE);
		}
		else
			ft_strappend(&arg, line[i], TRUE);
		i++;
	}
	return (arg);
}

char		**ms_parse(char *line)
{
	int		i;
	char	**buffer;
	char	**args;
	char	*arg;

	i = ft_skipspaces(line);
	if (!(buffer = NULL) && line[i] && (i--) != -1)
	{
		while (line[++i])
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				arg = ms_get_arg(line + i);
				ft_putintab(&buffer, arg);
				i = i + ft_strlen(arg) - 1;
				ft_strdel(&arg);
			}
		}
		args = ms_expand_args(buffer);
		ft_freetable(&buffer);
		return (args);
	}
	return (NULL);
}
