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

# define SQ 39
# define DQ 34
# define BS 92

#endif
