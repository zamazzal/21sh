/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:11:24 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/22 17:04:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

struct winsize	ft_winsize(void)
{
	struct winsize ts;

	ioctl(0, TIOCGWINSZ, &ts);
	ts.ws_col--;
	return (ts);
}

void			ft_putnstr(char *str, int n)
{
	while (n > 0)
	{
		ft_putstr(str);
		n--;
	}
}

int				is_empty(char *str)
{
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] != ' ')
				return (0);
			i++;
		}
	}
	return (1);
}

int				open_file(char *path, int oflags)
{
	int			fd;
	struct stat	st;

	if (lstat(path, &st) == -1 && oflags == O_RDONLY)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	fd = open(path, oflags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (fd);
}
