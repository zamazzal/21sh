/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 19:48:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/21 16:10:05 by zamazzal         ###   ########.fr       */
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
# define TYPE 7
# define BUFFER_SIZE 8000
# define HTABLE_SIZE 1000000

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
# define ALTU 1096489755
# define ALTD 1113266971
# define ALTC 42947
# define ALTV 10127586
# define ALTX 8948194
# define ALTF 37574
# define ALTG 43458
# define ALTA 42435
# define CTRLD 4
# define TAP 9
# define CTRLR 18

/*
**		Macros
*/

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"

# define PROMPT 1
# define SQ 39
# define DQ 34
# define BQ 96
# define BS 92
# define PIPE 124
# define HERDOC 42

# define LS 0
# define LD 1
# define RS 2
# define RD 3

# define PROMPTLINE ft_prompt(0)
# define BSPROMPT 2
# define DQPROMPT 8
# define QPROMPT 7
# define BQPROMPT 8
# define PIPEPROMPT 6
# define HERDOCPROMPT 9

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
**		DataStructure
*/

typedef struct	s_semiherdoc
{
	char				**content;
	struct s_semiherdoc	*next;
}				t_semiherdoc;

typedef struct	s_herdoc
{
	t_semiherdoc	*semiherdoc;
	struct s_herdoc	*next;
}				t_herdoc;

typedef	struct	s_getlines
{
	int i;
	int p;
	int f;
}				t_getlines;

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

typedef struct	s_cpy
{
	char		*buffer;
	int			p1;
	int			p2;
}				t_cpy;

typedef struct	s_red
{
	char			*right;
	char			*left;
	char			*o_right;
	char			*o_left;
	unsigned int	type:2;
	int				pos;
	struct s_red	*next;
}				t_red;

typedef	struct	s_afterred
{
	int		fd;
	char	*cmd;
}				t_afterred;

typedef struct	s_pos_tab
{
	int					pos;
	int					type;
	struct s_pos_tab	*next;
}				t_pos_tab;

typedef struct	s_to_close
{
	int					fd;
	struct s_to_close	*next;
}				t_to_close;

typedef struct	s_hashtable
{
	char				*cmd;
	char				*content;
	struct s_hashtable	*next;
}				t_hashtable;

typedef struct	s_fd
{
	int f[3];
}				t_fd;

/*
**		Variables
*/

char			**g_environ;
int				g_pid;
int				g_input_type;
char			*g_input;
int				g_pipe;
t_cursor		g_cursor;
t_cpy			g_cpy;
t_hashtable *g_htable[HTABLE_SIZE];
char			*g_search;
char			*g_autoc;
int				g_pars;

/*
**		builtins
**		sources/builtins
*/

void			ft_unsetenv(char **name);
void			ft_type(char *cmd);
void			ft_setinenv(int argc, char **argv);
void			ft_setenv(char *name, char *content);
char			*ft_getenv(const char *name);
void			ft_env(void);
void			ft_echo(int argc, char **argv);
void			ft_cd(char **argv);
int				ft_isbuiltin(char *cmd);
int				ft_builtins(char **argv, t_info info);

/*
**		execution
**		sources/execution
*/

unsigned long	ft_hash(char *str);
void			ft_freeh_htab(void);
void			exec_cmd(char *exec, char **argv, int fd);
char			*ft_iscmd(char *cmd);
int				ft_commands(char **argv, char *name, int fd);

/*
**		expansion
**		sources/expansion
*/

char			*ms_get_arg(char *line);
char			**ms_parse(char *line);
char			*ms_expand_quotes(char *arg);
char			*ms_expand_arg(char *arg);
void			ms_set_quote(int *quoted, char *quote, char c);

/*
**		messages
**		sources/messages
*/

int				ft_prompt(int mode);
void			ft_namerror(char *name);
void			ft_cmderror(char *cmd);
void			ft_permerror(char *cmd);
void			ft_notdir(char *name);
void			ft_puterror(char *error);

/*
**		parsing
**		sources/parsing
*/

int				checkbackslash(char *ptr, int i);
char			**ft_cmdsplit(char *ptr, int c);

/*
**		readline
**		sources/readline
*/

t_cursor		ft_autocompletion(t_cursor cursor);

char			*ft_endbackslash(char *cmd, char **history);
int				ft_checkbackslash(char *cmd);
void			ft_clearbuffer(void);
t_cursor		ft_straddchrinpos(char c, t_cursor cursor);
t_cursor		ft_addstrtostr(char *str2, t_cursor cursor);
int				ft_strisprint(char *str);
int				ft_checkcmds(char **array);
void			ft_copy(void);
t_cursor		ft_paste(t_cursor cursor);
t_cursor		ft_altx(t_cursor cursor);
int				doctrld(int key, int mode);
t_cursor		ft_checknoprint(int key, t_cursor cursor,
char **history, int *i);
int				ft_checkkey(int i);
int				ft_readx(void);
int				ft_getlinelen(int y);
char			*ft_removeantin(char *str);
char			*makecmdclear(char *cmd, char **history);
t_cursor		ft_defaultcursor(t_cursor *cursor);
t_cursor		ft_curright(t_cursor cur, int i);
t_cursor		ft_curleft(t_cursor cur, int i);
int				ft_getlines(void);
int				ft_firstinstr(char *str, int pos);
int				ft_getlastpos(char *str, int pos);
int				ft_getnextpos(char *str, int pos);
void			ft_calcpos(t_cursor *cursor, int prompt, int *p);
void			ft_endinput(char **cmds, char *input);
t_cursor		ft_right(t_cursor cursor);
t_cursor		ft_left(t_cursor cursor);
t_cursor		ft_up(int *i, t_cursor cursor, char **history);
t_cursor		ft_down(int *i, t_cursor cursor, char **history);
t_cursor		ft_home(t_cursor cursor);
t_cursor		ft_end(t_cursor cursor);
t_cursor		ft_backspace(t_cursor cursor);
t_cursor		ft_altr(t_cursor cursor);

void			ft_cpy();

t_cursor		ft_altl(t_cursor cursor);
t_cursor		ft_altu(t_cursor cursor);
t_cursor		ft_altd(t_cursor cursor);
int				ft_checkpipe(char *cmd);
char			*ft_closepipe(char *cmd, char **history);
int				ft_checkquote(char *cmd);
char			*ft_closequotes(char *cmd, char **history);
int				ft_promptlen(void);
void			ft_preparereadline(int *i, char **history);
void			ft_canelwithn(void);

char			*readline5(char **history, int *x);
char			*readline2(char **history);
char			*readline3(char **history, int *x);
char			*readline4(char **history, int *x);
char			*readline(char **history);

t_cursor		ft_ctrlr(t_cursor cursor, char **history);
t_cursor		ft_altright(t_cursor cursor);
t_cursor		ft_altleft(t_cursor cursor);
void			ft_termmanager(char *g_input, t_cursor g_cursor);
void			ft_current_cursor(t_cursor g_cursor);

/*
**		redirections
**		sources/redirections
*/

int				open_file(char *path, int oflags);
void			clean_reds_wings(t_red *reds);
void			escape_spaces(char **right_buf);
char			*prep_amp(t_red *red, int *len, int *left_fd);
int				exec_ls_red(t_red *red, int *fd);
int				exec_rd_red(t_red *red, int *fd);
t_afterred		exec_reds(char *cmd, int *status, t_to_close **toclose);
void			exec_red(t_red *red, int *aft_fd,
int *status, t_to_close **toclose);
int				exec_rs_red(t_red *red, int *fd);
t_red			*extract_reds(char *cmd);
void			append_toclose(t_to_close **head, int fd);
void			close_toclose(t_to_close **head);
char			*get_clean_cmd(char *cmd, t_red *reds);
int				valid_right_chars(char *right);
int				valid_left_chars(char *left, int type);
char			**get_red_wings(char *cmd, t_pos_tab *node);
int				ambiguous_red(t_red *red);
int				redirect_ltor(int left_fd, char *buf, int close_right, int *fd);
void			free_pos_tab(t_pos_tab **pos_tab);
t_pos_tab		*get_reds_positions(char *cmd);

/*
**		validation
**		sources/validation
*/

int				parseerror(char *cmd, int mode);
int				count_red(char *cmd, int start, int same);
int				check_reds(char *cmd, int end);
int				ft_redirerror(char *cmd);
char			**createcmds(char *input);

/*
**		tools
**		sources/tools
*/

int				ft_tablen(char **array);
void			ft_freetable(char ***array);
int				ft_strinstr(const char *s1, const char *s2, int len);
char			*ft_strjoin_lite(char *s1, char const *s2);
char			*ft_strsub_lite(char *s, unsigned int start, size_t len);
char			*ft_strdupc(char c);
char			*ft_straddchr(char *str, char c);
void			double_free(char *dead1, char **dead2);
void			extra_free(char *dead1, char *dead2);
int				ft_checkc(char *str, char c);
int				ft_skipspaces(char *str);
char			**ft_tabdup(char **array);
int				ft_strisnum(char *str);
int				ft_putchr(int c);
int				ft_checkcinstr(char *ptr, int c);
char			*ft_strappend(char **a_s1, char c, int overwrite);
int				quote_end(char *cmd, int start);
char			*ft_strojoin(char **s1, char *s2, int overwrite);
void			ft_putintab(char ***a_chain, char *entry);
struct winsize	ft_winsize(void);
void			ft_putnstr(char *str, int n);

/*
**		shell
**		sources/shell
*/

int				ft_freeherdoc(t_herdoc *herdoc);
char			*get_herdoc_right(char *str);
void			ft_cancel(void);
void			ft_signal(int x);
void			ft_winch(int x);
char			**ft_addtotab(char **tabl, char *str);
void			ft_shell(void);

int				ft_putcmds(char **cmd, char **history);
int				putcmd(char *cmd, char **cmds
, t_info info, t_to_close **toclose);
t_herdoc		*ft_herdoc(char **cmds, char **history, int *status);
int				ft_pipe(int *fd, int f, char *cmd);
int				ft_hdexec(char **heredoc);
int				ft_reds(char *cmd, t_to_close **toclose, t_afterred *red);
int				ft_exec_cmd(char **cmds, t_fd fd, t_semiherdoc *semiherdoc);
void			ft_waitpids(void);

/*
**		terminal
**		sources/terminal
*/

void			ft_cursmove(char c, int i);
int				ft_getcurpos2(void);
int				ft_getcurpos(void);
int				ft_putterm(char *t);
void			ft_term_prepare(int mode);
int				ft_tinit(void);
int				ft_checktitty(void);

#endif
