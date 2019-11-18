/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:19:25 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 16:36:48 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ms_expand_quotes(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	quote = 0;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (quoted == FALSE && ft_strchr("\'\"", arg[i]))
			i++;
		else if (arg[i] != quote)
			ft_strappend(&result, arg[i++], TRUE);
		else
			i++;
	}
	return (result);
}

static int	ms_expand_dollar(char **buffer, char *arg)
{
	int		i;
	char	*var_name;
	char	*val;

	var_name = ft_strnew(0);
	i = 0;
	while (arg[i] && ft_strchr(ALNUM, arg[i]))
	{
		ft_strappend(&var_name, arg[i], TRUE);
		i++;
	}
	if ((val = ft_getenv(var_name)))
		ft_strojoin(buffer, val, TRUE);
	ft_strdel(&var_name);
	return (i);
}

static char	*ms_expand_dollars(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (arg[i] == '$')
		{
			if ((quoted == TRUE && quote == DQ) || (quoted == FALSE))
			{
				i++;
				i += ms_expand_dollar(&result, arg + i);
				continue ;
			}
		}
		ft_strappend(&result, arg[i], TRUE);
		i++;
	}
	return (result);
}

static char	*ms_expand_tilde(char *arg)
{
	char	*result;
	char	*value;

	result = ft_strnew(0);
	if (arg[0] == '~')
	{
		if ((value = ft_getenv("HOME")))
			ft_strojoin(&result, value, TRUE);
		ft_strojoin(&result, arg + 1, TRUE);
		return (result);
	}
	ft_strdel(&result);
	result = ft_strdup(arg);
	return (result);
}

char		*ms_expand_arg(char *arg)
{
	char	*result;
	char	*tmp;

	result = ms_expand_tilde(arg);
	tmp = ft_strdup(result);
	ft_strdel(&result);
	result = ms_expand_dollars(tmp);
	ft_strdel(&tmp);
	tmp = ft_strdup(result);
	ft_strdel(&result);
	result = ms_expand_quotes(tmp);
	ft_strdel(&tmp);
	return (result);
}
