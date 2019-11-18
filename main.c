/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/09/16 19:57:36 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**ctables(char **array)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			len = ft_strlen(array[i]);
			if (array[i][0] == SQ && array[i][len - 1] == SQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == DQ && array[i][len - 1] == DQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == BQ && array[i][len - 1] == BQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			i++;
		}
		return (array);
	}
	return (NULL);
}

int				ft_checkred(char *cmd)
{
	if (ft_checkcinstr(cmd, '<'))
		return (1);
	if (ft_checkcinstr(cmd, '>'))
		return (1);
	return (0);
}

int **ft_createpipes(int piplen)
{
	int i;
	int **pipes;

	SAFE(pipes = (int **)malloc(sizeof(int*) * piplen));
	i = 0;
	while (i < piplen)
	{
		SAFE(pipes[i] = (int *)malloc(sizeof(int) * 2));
		if (pipe(pipes[i]) == -1)
		{
			ft_puterror("pipe error");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void			ft_closepipes(int **pipes, int piplen)
{
	int i;

	i = 0;
	while (i < piplen)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int			putcmd(char *cmd, char **cmds, t_info info)
{
	char **argv;

	argv = ms_parse(cmd);
	if (!(ft_builtins(ctables(argv), info)))
	{
		ft_freetable(&cmds);
		ft_freetable(&argv);
		return (1);
	}
	ft_freetable(&argv);
	return (0);
}

void		ft_inputdone(int fd)
{
	dup2(fd, 0);
	close(fd);
}

int		ft_pipe(int *fd, int f)
{
	int p[2];

	if (pipe(p) == -1)
		return (-1);
	*fd = p[0];
	if (f != -1)
		dup2(p[1], f);
	else
		dup2(p[1], 1);
	close(p[1]);
	return (p[1]);
}

void			ft_backline()
{
	int x;

	x = ft_getcurpos2();
	if (x > 1)
	{
		ft_putterm("mr");
		ft_putchar('%');
		ft_putterm("me");
		ft_putchar(' ');
		ft_putchar('\n');
	}
}

void			ft_waitpids(void)
{
	int r;
	int x;

	r = wait(NULL);
	x = 0;
	while (r > 0)
	{
		x++;
		r = wait(NULL);
	}
	if (x)
		ft_backline();
}

void			ft_endcmds(char **cmds, int fd)
{
	dup2(fd, 0);
	ft_waitpids();
	g_pid = 0;
	ft_freetable(&cmds);
}

int	ft_herdocexec(char **heredoc)
{
	int p[2];
	int i;

	i = 0;
	if (!heredoc)
		return (0);
	if (pipe(p) == -1)
		return (1);
	dup2(p[0], 0);
	close(p[0]);
	while (heredoc[i] != NULL)
	{
		ft_putendl_fd(heredoc[i], p[1]);
		i++;
	}
	ft_freetable(&heredoc);
	close(p[1]);
	return (0);
}

int		ft_putcmd(char *cmd, t_semiherdoc *semiherdoc)
{
	char **cmds;
	int i;
	int f[3];
	int p[2];
	t_info	info;
	t_afterred	red;
	//int		status;
	int		*fd_buf;
	t_semiherdoc *tmp;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return (1);
	i = 0;
	f[0] = dup(0);
	f[1] = dup(1);
	f[2] = dup(2);
	info.fd = -1;
	info.mode = (ft_tablen(cmds) > 1) ? 1 : 0;
	fd_buf = NULL;
	while (cmds[i] != NULL)
	{
		if (ft_herdocexec(semiherdoc->content))
			return (1);
		/*append_fd_buf(&fd_buf, -1);
		status = 0;

		red = exec_reds(cmds[i], &status, &fd_buf);
		if (!red.cmd)
		{
			if (status == -1 && !(status = 0))
			{
				//close_fd_buf(&fd_buf);
				break ;
			}
		}*/
		if (i > 0)
			ft_inputdone(p[0]);
		if (cmds[i + 1] != NULL)
		{
			if ((p[1] = ft_pipe(&info.fd, red.fd)) == -1)
				return (1);
			p[0] = info.fd;
		}
		else
		{
			if (red.fd == -1)
				dup2(f[1], 1);
			else
				dup2(f[1], red.fd);
		}
		if (putcmd(cmds[i], cmds, info))
			return (1);
		//close_fd_buf(&fd_buf);
		i++;
		tmp = semiherdoc;
		semiherdoc = semiherdoc->next;
		free(tmp);
	}
	dup2(f[1], 1);
	dup2(f[2], 2);
	ft_endcmds(cmds, f[0]);
	close(f[0]);
	close(f[1]);
	close(f[2]);
	return (0);
}

char *get_herdoc_right(char *str)
{
	char *new;
	int i;

	i = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
		i++;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t'))
		i++;
	new = ms_get_arg(&str[i]);
	new = ms_expand_quotes(new);
	return (new);
}

char **putherdoc(char *str, char **history, int *status)
{
	char **herdoc;
	int i;

	herdoc = (char **)malloc(sizeof(char *));
	herdoc[0] = NULL;
	i = 0;
	ft_term_prepare(0);
	while (1337)
	{
		g_cursor = ft_defaultcursor(&g_cursor);
		ft_putterm("cr");
		ft_putstr("heredoc> ");
		g_input_type = HERDOC;
		g_input = readline4(history, &i);
		if (i == 1 || ft_strequ(g_input, str))
			break;
		herdoc = ft_addtotab(herdoc, g_input);
		ft_strdel(&g_input);
	}
	ft_term_prepare(1);
	if (i == 1)
	{
		*status = 1;
		return (NULL);
	}
	ft_strdel(&g_input);
	return (herdoc);
}

char **ft_getherd_content(char *cmd, char **history, int *status)
{
	char **herdoc;
	char *ptr;
	char *str;

	herdoc = NULL;
	ptr = cmd;
	while ((ptr = ft_strstr(ptr, "<<")))
	{
		ptr = ptr + 2;
		str = get_herdoc_right(ptr);
		if (herdoc)
			ft_freetable(&herdoc);
		herdoc = putherdoc(str, history, status);
		if (*status)
			break;
	}
	return (herdoc);
}


t_semiherdoc *ft_semiherdoc(char *cmd, char **history, int *status)
{
	int i;
	t_semiherdoc *sherdoc;
	t_semiherdoc *head;
	char **sub;

	i = 0;
	if (!(sub = ft_cmdsplit(cmd, '|')))
		return (NULL);
	if (!(sherdoc = (t_semiherdoc*)malloc(sizeof(t_semiherdoc))))
		return (NULL);
	head = sherdoc;
	while (sub[i] != NULL)
	{
		sherdoc->content = ft_getherd_content(sub[i], history, status);
		if (*status)
			break;
		if (sub[i + 1] != NULL)
		{
			sherdoc->next = (t_semiherdoc*)malloc(sizeof(t_semiherdoc));
			sherdoc = sherdoc->next;
		}
		i++;
	}
	ft_freetable(&sub);
	sherdoc->next = NULL;
	return (head);
}

t_herdoc *ft_herdoc(char **cmds, char **history, int *status)
{
	t_herdoc *herdoc;
	t_herdoc *head;
	int len;
	int i;

	len = ft_tablen(cmds);
	if (!(herdoc = (t_herdoc*)malloc(sizeof(t_herdoc))))
		return (NULL);
	i = 0;
	head = herdoc;
	while (cmds[i] != NULL)
	{
		herdoc->semiherdoc = ft_semiherdoc(cmds[i], history, status);
		if (*status)
			break;
		if (cmds[i + 1] != NULL)
		{
			herdoc->next = (t_herdoc*)malloc(sizeof(t_herdoc));
			herdoc = herdoc->next;
		}
		i++;
	}
	herdoc->next = NULL;
	return (head);
}

void		ft_putherdocs(t_herdoc *herdoc)
{
	t_semiherdoc *tmp;

	while (herdoc)
	{
		tmp = herdoc->semiherdoc;
		while (tmp)
		{
			ft_putendl("\n=============");
			ft_puttables(tmp->content);
			ft_putendl("=============");
			tmp = tmp->next;
		}
		herdoc = herdoc->next;
	}
}

int			ft_putcmds(char **cmd, char **history)
{
	int i;
	char **clone;
	t_herdoc *herdoc;
	t_herdoc *head;
	int status;

	i = 0;
	status = 0;
	clone = ft_tabdup(cmd);
	herdoc = ft_herdoc(clone, history, &status);
	ft_freetable(&clone);
	if (status) // free list
		return (0);
	head = herdoc;
	//ft_putherdocs(herdoc);
	while (cmd[i] != NULL)
	{
		if (ft_putcmd(cmd[i], head->semiherdoc))
			return (1);
		i++;
		herdoc = head;
		head = head->next;
		free(herdoc);
	}
	free(head);
	return (0);
}

static char		**creation(char **table)
{
	char	**new;

	g_pid = 0;
	new = ft_tabdup(table);
	return (new);
}
void			ft_cpy()
{
	g_cpy.p1 = -1;
	g_cpy.p2 = -1;
}

int				main(void)
{
	extern char		**environ;

	if (ft_tinit() == -1 || ft_checktitty())
		return (0);
	signal(SIGINT, ft_signal);
	signal(SIGWINCH, ft_winch);
	SAFE(g_environ = creation(environ));
	g_input_type = 0;
	ft_shell();
	ft_freetable(&g_environ);
	return (1);
}
