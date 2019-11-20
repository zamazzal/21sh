/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:23:24 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 16:25:44 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ms_set_quote(int *quoted, char *quote, char c)
{
	if (c == SQ && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == SQ && (*quoted) == TRUE && (*quote) == SQ)
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
	else if (c == DQ && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == DQ && (*quoted) == TRUE && (*quote) == DQ)
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
}
