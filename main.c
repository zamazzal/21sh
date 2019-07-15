/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/07/15 19:54:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

size_t			ft_getindex(char *str, char c)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
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

int				ft_morecmd(char *str)
{
	int i;
	int len;

	len = ft_strlen(str) - 1;
	i = 0;
	if (str[len] == '\\')
	{
		while (str[len] == '\\')
		{
			len--;
			i++;
		}
	}
	if (i % 2 == 0 || i == 0)
		return (0);
	return (1);
}

char			*ft_strjoin_lite(char *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(ptr = (char*)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (s1)
		ft_strdel(&s1);
	return (ptr);
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

int	ft_checkcot(char *cmd)
{
	int		i;
	char	c;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == DQ || cmd[i] == SQ || cmd[i] == '`')
		{
			c = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
			if (cmd[i] == '\0')
				return (c);
		}
		i++;
	}
	return (0);
}

static int		ft_strisprint(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] >= 33 && str[i] <= 126)
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_removeantin(char *str)
{
	int r;

	if ((r = ft_getindex(str, '\n')) > 0)
		str = ft_strsub_lite(str, 0, r);
	return (str);
}

char	*ft_closecotes(char *cmd)
{
	int		r;
	char	*input;

	input = ft_strnew(BUFFER_SIZE);
	while ((r = ft_checkcot(cmd)))
	{
		if (r == DQ)
			ft_putstr("dquote> ");
		else if (r == SQ)
			ft_putstr("quote> ");
		else if (r == '`')
			ft_putstr("bquote> ");
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || !ft_strisprint(input))
			continue ;
		cmd = ft_strjoin_lite(cmd, input);
	}
	cmd = ft_removeantin(cmd);
	ft_strdel(&input);
	return (cmd);
}

char	*ft_endcmd(char *cmd)
{
	int		r;
	char	*input;
	int		len;

	input = ft_strnew(BUFFER_SIZE);
	while ((r = ft_morecmd(cmd)))
	{
		ft_putstr("> ");
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || !ft_strisprint(input))
			continue ;
		len = ft_strlen(cmd);
		if (len > 1)
			cmd = ft_strjoin_lite(ft_strsub_lite(cmd, 0, len - 1), input);
		else
		{
			ft_strdel(&cmd);
			cmd = ft_strdup(input);
		}
		cmd = ft_removeantin(cmd);
	}
	ft_strdel(&input);
	return (cmd);
}

int	ft_inputerror(char *input, int mode)
{
	if (parseerror(input, mode))
		return (1);
	if (!ft_strisprint(input))
		return (1);
	return (0);
}

char	*goodcmd(char *cmd)
{
	cmd = ft_closecotes(cmd);
	cmd = ft_endcmd(cmd);
	return (cmd);
}

int		ft_checkcmds(char **array)
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

int		main(int argc, char **argv)
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
		input = goodcmd(input);
		if (!(cmds = ft_cmdsplit(input, ';')))
			break ;
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
