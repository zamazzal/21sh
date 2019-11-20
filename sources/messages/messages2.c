/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:38:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:43:14 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_prompt(void)
{
	char *user;

	user = ft_getenv("USER");
	ft_putstr("mysh");
	ft_strequ(user, "root") ? ft_putstr("# ") : ft_putstr("$ ");
}

void	ft_namerror(char *name)
{
	if (name)
		ft_putstr(name);
	ft_putendl(" : command not found");
}

void	ft_cmderror(char *cmd)
{
	if (cmd)
		ft_putstr(cmd);
	ft_putendl(" : No such file or directory");
}

void	ft_permerror(char *cmd)
{
	if (cmd)
		ft_putstr(cmd);
	ft_putendl(" : Permission denied");
}

void	ft_notdir(char *name)
{
	if (name)
		ft_putstr(name);
	ft_putendl(" : not a directory");
}
