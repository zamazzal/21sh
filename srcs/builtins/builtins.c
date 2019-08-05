/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:50:45 by zamazzal          #+#    #+#             */
/*   Updated: 2019/04/28 20:14:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_do_bui(char **argv, char *cmd, int rtn)
{
	int argc;

	if (!argv || !cmd)
		return ;
	argc = ft_tablen(argv);
	if (rtn == ECHO)
		ft_echo(argc, argv);
	else if (rtn == ENV)
		ft_env();
	else if (rtn == SETENV)
		ft_setinenv(argc, argv);
	else if (rtn == UNSETENV)
		ft_unsetenv(argv);
	else if (rtn == CD)
		ft_cd(argv);
}

static char		**ft_edit(char **argv)
{
	size_t	len;
	size_t	i;
	char	**new;

	if (!argv)
		return (NULL);
	i = 0;
	len = ft_tablen(argv);
	if (!(new = (char **)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (argv[i][0] == '$' && ft_isprint(argv[i][1]))
			new[i] = ft_strdup(ft_getenv(&argv[i][1]));
		else if (argv[i][0] == '~')
			new[i] = ft_strjoin(ft_getenv("HOME"), &argv[i][1]);
		else
			new[i] = ft_strdup(argv[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int				ft_builtins(char **argv)
{
	char	**args;
	char	*cmd;
	int		rtn;

	if (!argv)
		return (1);
	args = ft_edit(argv);
	cmd = ft_strdup(args[0]);
	rtn = ft_commands(args, cmd);
	if (rtn != 0 && rtn != 100)
	{
		if (rtn == EXIT)
		{
			double_free(cmd, args);
			return (0);
		}
		ft_do_bui(args, cmd, rtn);
	}
	if (rtn == 100)
		ft_namerror(cmd);
	double_free(cmd, args);
	return (1);
}
