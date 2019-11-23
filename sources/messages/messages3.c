/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 00:07:41 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/21 15:31:21 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*getuser(void)
{
	char *user;

	user = ft_strdup(ft_getenv("USER"));
	return (user);
}

static char	*gethost(void)
{
	char host[1024];

	host[1023] = '\0';
	gethostname(host, 1023);
	return (ft_strdup(host));
}

static void	ft_showprompt(char *user, char *host, char *path)
{
	if (user)
	{
		ft_putstr(GREEN);
		ft_putstr(user);
	}
	if (user && host)
		ft_putchar('@');
	if (host)
	{
		ft_putstr(GREEN);
		ft_putstr(host);
	}
	if ((user || host) && path)
	{
		ft_putstr(DEFAULT);
		ft_putchar(':');
	}
	if (path)
	{
		ft_putstr(BLUE);
		ft_putstr(path);
	}
	ft_putstr(DEFAULT);
	(user && ft_strequ(user, "root")) ? ft_putstr("#") : ft_putstr("$");
	ft_putchar(' ');
}

static int	ft_getlen(char *user, char *host, char *path)
{
	int				len;
	struct winsize	ts;

	len = 2;
	if (user)
		len += ft_strlen(user);
	if (user && host)
		len++;
	if (host)
		len += ft_strlen(host);
	if ((user || host) && path)
		len++;
	if (path)
		len += ft_strlen(path);
	ts = ft_winsize();
	while (len > ts.ws_col)
		len -= ts.ws_col;
	return (len);
}

int			ft_prompt(int mode)
{
	char	*user;
	char	*host;
	char	*path;
	int		len;

	user = getuser();
	host = gethost();
	path = ft_strdup(ft_getenv("PWD"));
	if (mode)
	{
		ft_showprompt(user, host, path);
		ft_strdel(&user);
		ft_strdel(&host);
		ft_strdel(&path);
		ft_putstr(DEFAULT);
		return (0);
	}
	len = ft_getlen(user, host, path);
	ft_strdel(&user);
	ft_strdel(&host);
	ft_strdel(&path);
	return (len);
}
