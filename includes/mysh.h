/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 19:48:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/10/15 15:59:29 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSH_H
# define MYSH_H

/*
**		Libraries
*/

# include "libft.h"
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

/*
**		Indexes of Builtins
*/

# define XECHO 1
# define CD 2
# define SETENV 3
# define UNSETENV 4
# define ENV 5
# define EXIT 6
# define BUFFER_SIZE 1024

/*
**		Keys
*/

# define ENTRE 10
# define RIGHT 4414235
# define LEFT 4479771
# define UP 4283163
# define DOWN 4348699
# define ESC 27
# define BACKSPACE 127
# define HOME 4741915
# define END 4610843
# define ALTR 1130044187
# define ALTL 1146821403

/*
**		Colors
*/

# define DEFAULT "\033[0m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define MAGENTA "\033[35;1m"
# define CYAN "\033[36;1m"
# define GRAY "\033[90;1m"

/*
**		Malloc Protection
*/

# define SAFE(expr) if (!(expr)) return (0)

/*
**		Variables
*/

typedef struct	s_info
{
	int			fd;
	int			mode;
}				t_info;

typedef struct	s_cursor
{
	int			x;
	int			y;
	int			pos;
}				t_cursor;

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"

char			**g_environ;
int				g_pid;
int				g_input_type;
char			*g_input;
int				g_pipe;
t_cursor		g_cursor;

# define SQ 39
# define DQ 34
# define BQ 96
# define BS 92
# define BUFFER_SIZE 1024
# define PROMPTLINE 6

/*
**		shell
**		srcs/shell
*/

char			*ft_prepareinput(void);
void			ft_endinput(char **cmds, char *input);
char			**createcmds(char *input);
void			ft_shell(void);
char			*readline(char **history);
char			*readline2(char **history);
int				ft_putcmds(char **cmd);
t_cursor		ft_checknoprint(int key, t_cursor cursor, char **history, int *i);

/*
**		input
**		srcs/input
*/

int				checkbackslash(char *ptr, int i);
char			*makecmdclear(char *cmd, char **history);
char			*ft_endbackslash(char *cmd, char **history);
char			*ft_closepipe(char *cmd, char **history);
char			*ft_closequotes(char *cmd, char **history);
int				ft_checkquote(char *cmd);
int				ft_checkbackslash(char *cmd);
int				ft_checkpipe(char *cmd);
char			*ft_removeantin(char *str);
int				ft_inputerror(char *input, int mode);
int				ft_checkcmds(char **array);
int				ft_strisprint(char *str);

/*
**		Builtins
**		srcs/builtins
*/

char			*ft_getenv(const char *name);
void			ft_setinenv(int argc, char **argv);
void			ft_setenv(char *name, char *content);
void			ft_echo(int argc, char **argv);
void			ft_env(void);
int				ft_builtins(char **argv, t_info info);
void			ft_unsetenv(char **name);
void			ft_cd(char **argv);

/*
**		Commands
**		srcs/commands
*/

char			**ms_parse(char *line);
char			*ms_expand_arg(char *arg);
void			ms_set_quote(int *quoted, char *quote, char c);
int				ft_commands(char **argv, char *name, int fd);
void			exec_cmd(char *exec, char **argv, int fd);

/*
**		errors
**		srcs/errors
*/

int				check_reds(char *cmd, int end);
int				ft_redirerror(char *cmd);
int				parseerror(char *cmd, int mode);
void			ft_puterror(char *error);

/*
**		parsing
**		srcs/parsing
*/

char			**ft_cmdsplit(char *ptr, int c);

/*
**		termcaps
**		srcs/term
*/

int				ft_checktitty(void);
int				ft_tinit(void);
void			ft_term_prepare(int mode);
void			ft_term_canon(void);
void			ft_term_nocanon(void);
void			ft_term_echo(void);
void			ft_term_noecho(void);
int				ft_putchr(int c);
int				ft_putterm(char *t);
void            ft_cursmove(char c, int i);
int				ft_readshow(char *cmd);
void			ft_termmanager(char *g_input, t_cursor g_cursor);
t_cursor		ft_curright(t_cursor cur, int i);
t_cursor		ft_curleft(t_cursor cur, int i);
t_cursor	ft_defaultcursor(t_cursor *cursor);
struct winsize	ft_winsize(void);
void	ft_current_cursor(t_cursor g_cursor);
void		ft_cancel(void);

/*
**		signals
**		srcs/signals
*/

void			ft_signal(int x);
void			ft_winch(int x);

/*
**		Messages
**		srcs/messages
*/

void			ft_prompt(void);
void			ft_namerror(char *name);
void			ft_cmderror(char *cmd);
void			ft_permerror(char *cmd);
void			ft_notdir(char *name);
void			ft_putnstr(char *str, int n);

/*
**		Tools
**		srcs/tools
*/

char			**ft_tabdup(char **array);
void			extra_free(char *dead1, char *dead2);
void			double_free(char *dead1, char **dead2);
void			ft_freetable(char ***array);
int				ft_strinstr(const char *s1, const char *s2, int len);
int				ft_checkcinstr(char *ptr, int c);
char			*ft_strjoin_lite(char *s1, char const *s2);
char			*ft_strsub_lite(char *s, unsigned int start, size_t len);
int				ft_tablen(char **array);
int				ft_straddchr(char *str, char c);
t_cursor		ft_straddchrinpos(char c, t_cursor cursor);
char			*ft_strappend(char **a_s1, char c, int overwrite);
int				quote_end(char *cmd, int start);
char			*ft_strojoin(char **s1, char *s2, int overwrite);
void			ft_putintab(char ***a_chain, char *entry);
int				ft_skipspaces(char *str);
char			**ft_addtotab(char **tabl, char *str);

#endif
