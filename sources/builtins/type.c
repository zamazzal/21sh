/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:12:16 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 22:17:44 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_type(char *cmd)
{
	char *path;

	if (!cmd)
		return ;
	if (ft_isbuiltin(cmd))
	{
		ft_putstr(cmd);
		ft_putendl(" is a shell builtin");
	}
	else if ((path = ft_iscmd(cmd)))
	{
		ft_putstr(cmd);
		ft_putstr(" is ");
		ft_putendl(path);
		ft_strdel(&path);
	}
	else
	{
		ft_putstr(cmd);
		ft_putendl(" not found");
	}
}
