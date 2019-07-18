/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 19:48:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/11 20:14:48 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSH_H
# define MYSH_H

# include <stdio.h>
# include "libft.h"

typedef struct	s_subcmds
{
	char				*cmd;
	struct s_subcmds	*next;
}				t_subcmds;

typedef	struct	s_cmds
{
	t_subcmds		*cmds;
	struct s_cmds	*next;
}				t_cmds;

char	**g_environ;
int		g_pid;

# define SAFE(expr) if (!(expr)) return (0)
# define SQ 39
# define DQ 34
# define BS 92
# define BUFFER_SIZE 1024

char			**ft_cmdsplit(char *ptr, int c);
int				parseerror(char *cmd, int mode);

void			ft_freetable(char **array);
void			ft_freexlistes(t_cmds *cmds);
void			ft_freelistes(t_subcmds *cmds);

t_subcmds		*putcommand(char **cmds);
t_cmds			*splitcmds(char **array);

char			*ft_removeantin(char *str);
int				ft_inputerror(char *input, int mode);
int				ft_checkcmds(char **array);
int				ft_strinstr(const char *s1, const char *s2, int len);
char			*ft_strjoin_lite(char *s1, char const *s2);
char			*ft_strsub_lite(char *s, unsigned int start, size_t len);
int				ft_strisprint(char *str);
void			ft_putnstr(char *str, int n);
int				ft_tablen(char **array);

int	ft_checkquote(char *cmd);
int	ft_checkbackslash(char *cmd);
int	ft_checkpipe(char *cmd);

char	*makecmdclear(char *cmd);
char	*ft_endbackslash(char *cmd);
char	*ft_closepipe(char *cmd);
char	*ft_closequotes(char *cmd);

#endif
