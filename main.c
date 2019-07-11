/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/07/11 20:07:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_freetable(char **array)
{
	int i;

	i = 0;
	if (*array)
	{
		while (array[i] != NULL)
			ft_strdel(&array[i++]);
		free(array);
	}
}

int checkbackslash(char *ptr, int i)
{
	int x;
	int c;

	x = i - 1;
	c = 0;
	while (x >= 0)
	{
		if (ptr[x] == BS)
			c++;
		if (ptr[x] != BS)
			break ;
		x--;
	}
	return (c);
}

int ft_getsemicol(char *ptr)
{
	int i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == DQ)
		{
			i++;
			while (ptr[i] && ptr[i] != DQ)
				i++;
		}
		if (ptr[i] == SQ)
		{
			i++;
			while (ptr[i] && ptr[i] != SQ)
				i++;
		}
		if (ptr[i] == ';' && !(checkbackslash(ptr, i) % 2))
			return (i);
		i++;
	}
	return (-1);
}

int ft_nbrsemicol(char *ptr)
{
	int x;
	int nbr;

	nbr = 1;
	x = 0;
	while((x = ft_getsemicol(ptr)) != -1)
	{
		ptr += x + 1;
		if (x == 0)
			continue;
		if (*ptr == '\0')
			break ;
		nbr++;
	}
	return (nbr);
}

char **putcontent(char *ptr, int len)
{
	int i;
	int x;
	int chrlen;
	char **cmds;

	i = 0;
	if (!(cmds = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while ((x = ft_getsemicol(ptr)) != -1)
	{
		if (x != 0)
			cmds[i++] = ft_strsub(ptr, 0, x);
		ptr += x + 1;
	}
	chrlen = ft_strlen(ptr);
	if (chrlen > 0)
		cmds[i++] = ft_strsub(ptr, 0, chrlen);
	cmds[i] = NULL;
	return (cmds);
}

char **ft_cmdsplit(char *ptr)
{
	int len;

	len = ft_nbrsemicol(ptr);
	return (putcontent(ptr, len));
}

int doublesemicol(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == ';')
		{
			if (cmd[i + 1] && cmd[i + 1] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

int parseerror(char *cmd)
{
	if (doublesemicol(cmd))
		ft_putendl_fd("21sh : parse error near `;;'", 2);
	else
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	char **cmds;

	if (argc > 1)
	{
		if (parseerror(argv[1]))
			return (1);
		if (!(cmds = ft_cmdsplit(argv[1])))
			return (1);
		ft_puttables(cmds);
		ft_freetable(cmds);
	}
	return (0);
}
