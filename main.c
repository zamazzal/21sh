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

size_t			ft_getindex(char *str, char c)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int				ft_strinstr(const char *s1, const char *s2, int len)
{
	int i;
	int j;

	if (!s1)
		return (0);
	if (s2[0] == '\0')
		return (1);
	i = 0;
	while ((s1[i] != '\0') && (i < len))
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i + j] != s2[j] || j + i >= len)
				break ;
			j++;
		}
		if (s2[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char			*ft_getenv(const char *name)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	if (!name)
		return (NULL);
	env = ft_strjoin(name, "=");
	len = ft_strlen(env);
	while (g_environ[i] != NULL)
	{
		if (ft_strinstr(g_environ[i], env, len))
		{
			ft_strdel(&env);
			return (ft_strchr(g_environ[i], '=') + 1);
		}
		i++;
	}
	ft_strdel(&env);
	return (NULL);
}


char			*ft_strsub_lite(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || len <= 0 || (int)start < 0)
		return (NULL);
	if (!(ptr = (char*)malloc(len + 1)))
		return (NULL);
	while (i < len && s[start])
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	if (s)
		ft_strdel(&s);
	return (ptr);
}

void	ft_username(void)
{
	char *name;

	/*name = ft_getenv("USER");
	if (name)
		ft_putstr(name);*/
	ft_putstr("21sh");
	ft_putstr(" $> ");
}

int		ft_notspace(char c)
{
	if (c != 32)
		return (1);
	return (0);
}

void	ft_putlistes(t_subcmds *cmds)
{
	ft_putendl("-------*start*-------");
	while (cmds != NULL)
	{
		ft_putendl(cmds->cmd);
		cmds = cmds->next;
	}
	ft_putendl("-------*end*-------");
}

void	ft_putxlistes(t_cmds *cmds)
{
	while (cmds != NULL)
	{
		ft_putlistes(cmds->cmds);
		cmds = cmds->next;
	}
}

int	ft_closecot(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
		{
			while (cmd[i] && cmd[i] != '"')
				i++;
			if (cmd[i] == '\0')
				return (0);
		}
		if (cmd[i] == '\'')
		{
			while (cmd[i] && cmd[i] != '\'')
				i++;
			if (cmd[i] == '\0')
				return (0);
		}
		if (cmd[i] == '`')
		{
			while (cmd[i] && cmd[i] != '`')
				i++;
			if (cmd[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

static int		ft_strisprint(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] >= 33 && str[i] <= 126 && str[i] != '"')
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_inputerror(char *input, int mode)
{
	if (parseerror(input, mode))
		return (1);
	if (!ft_strisprint(input))
		return (1);
	return (0);
}

int ft_checkcmds(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_inputerror(array[i], 2))
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	int				r;
	char			*input;
	char			**cmds;
	t_cmds			*mycmds;

	while (1)
	{
		input = ft_strnew(BUFFER_SIZE);
		ft_username();
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || ft_inputerror(input, 1))
		{
			ft_strdel(&input);
			continue ;
		}
		if ((r = ft_getindex(input, '\n')) > 0)
			input = ft_strsub_lite(input, 0, r);
		if (!(cmds = ft_cmdsplit(input, ';')))
			break;
		if (ft_checkcmds(cmds))
		{
			ft_strdel(&input);
			continue ;
		}
		if (ft_strequ(input, "exit"))
			break ;
		mycmds = splitcmds(cmds);
		ft_freetable(cmds);
		ft_putxlistes(mycmds);
		ft_freexlistes(mycmds);
		ft_strdel(&input);
	}
	ft_freetable(cmds);
	ft_strdel(&input);
	return (0);
}
