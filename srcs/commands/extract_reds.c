/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_reds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:01:23 by aihya             #+#    #+#             */
/*   Updated: 2019/11/11 16:48:04 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_red *red_node(int type, char **wings)
{
	t_red *node;

	node = (t_red *)malloc(sizeof(t_red));
	node->type = type;
	node->right = ft_strdup(wings[0]);
	node->left = ft_strdup(wings[1]);
	node->next = NULL;
	return (node);
}

void set_pos_table(int ***pos_table, int index, int pos, int red_type)
{
	(*pos_table)[index] = (int *)malloc(sizeof(int) * 2);
	(*pos_table)[index][0] = pos;
	(*pos_table)[index][1] = red_type;
}

void append_red_node(t_red **a_head, t_red *node)
{
	t_red *curr;

	if (*a_head == NULL)
		*a_head = node;
	else
	{
		curr = *a_head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

int append_red_symbol(int ***pos_tab, int *c, char *cmd, int i)
{
	int k;
	char sym;

	sym = cmd[i];
	k = count_red(cmd, i, 1);
	if (k == 1)
		set_pos_table(pos_tab, (*c)++, i, (sym == '>' ? RS : LS));
	else if (k == 2)
		set_pos_table(pos_tab, (*c)++, i, (sym == '>' ? RD : LD));
	return (k);
}

int **get_reds_positions(char *cmd)
{
	int i;
	int c;
	int **pos_tab;

	pos_tab = (int **)malloc(sizeof(int *) * POS_MAX_LEN);
	c = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			i = quote_end(cmd, i);
			continue;
		}
		else if (ft_strchr("><", cmd[i]))
		{
			i += append_red_symbol(&pos_tab, &c, cmd, i);
			continue;
		}
		i++;
	}
	if (c == 0)
		return (NULL);
	pos_tab[c] = NULL;
	return (pos_tab);
}

char *get_right(char *cmd, int pos, int steps)
{
	int i;
	char *right;
	char q;

	right = NULL;
	i = pos + steps;
	while (cmd[i] && cmd[i] == ' ')
		ft_strappend(&right, cmd[i++], 1);
	while (cmd[i] && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(&right, cmd[i++], 1);
		if (cmd[i - 1] && ft_strchr("\"\'", cmd[i - 1]))
		{
			q = cmd[i - 1];
			while (cmd[i] != q)
				ft_strappend(&right, cmd[i++], 1);
			ft_strappend(&right, cmd[i++], 1);
		}
	}
	
	if (ft_strlen(right) == 1 && right[0] == '&')
	{
		while (cmd[i] && cmd[i] == ' ')
			ft_strappend(&right, cmd[i++], 1);
		while (cmd[i] && !ft_strchr("> <", cmd[i]))
		{
			ft_strappend(&right, cmd[i++], 1);
			if (ft_strchr("\"\'", cmd[i - 1]))
			{
				q = cmd[i - 1];
				while (cmd[i] != q)
					ft_strappend(&right, cmd[i++], 1);
				ft_strappend(&right, cmd[i++], 1);
			}
		}
	}
	return (right);
}

char *get_left(char *cmd, int pos)
{
	int i;
	char *left;
	char *tmp;
	char q;

	left = NULL;
	tmp = NULL;
	i = pos - 1;
	while (i >= 0 && cmd[i] == ' ')
		ft_strappend(&left, cmd[i--], 1);
	while (i >= 0 && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(&left, cmd[i--], 1);
		if (ft_strchr("\"\'", cmd[i + 1]))
		{
			q = cmd[i + 1];
			while (cmd[i] != q)
				ft_strappend(&left, cmd[i--], 1);
			ft_strappend(&left, cmd[i--], 1);
		}
	}
	if (left != NULL)
	{
		tmp = ft_strrev(left);
		free(left);
		left = ft_strdup(tmp);
		free(tmp);
	}
	return (left);
}

char **get_red_wings(char *cmd, int type, int pos)
{
	char **wings;

	wings = (char **)malloc(sizeof(char *) * 3);
	if (type == LS || type == RS)
	{
		wings[0] = get_right(cmd, pos, 1);
		wings[1] = get_left(cmd, pos);
	}
	else if (type == LD || type == RD)
	{
		wings[0] = get_right(cmd, pos, 2);
		wings[1] = get_left(cmd, pos);
	}
	wings[2] = NULL;
	return (wings);
}

t_red *extract_reds(char *cmd)
{
	t_red *head;
	t_red *node;
	char **wings;
	int i;
	int	**reds_pos;

	head = NULL;
	reds_pos = get_reds_positions(cmd);
	i = 0;
	if (reds_pos != NULL)
	{
		while (reds_pos[i] != NULL)
		{
			wings = get_red_wings(cmd, reds_pos[i][1], reds_pos[i][0]);
			node = red_node(reds_pos[i][1], wings);
			node->pos = reds_pos[i][0];
			append_red_node(&head, node);
			ft_chain_free(&wings);
			i++;
		}
	}
	return (head);
}

/*
int main(int argc, char **argv, char **envp)
{
	int **pos;
	char str[] = "/bin/ls >ms";
	t_red *reds;
	t_red	*curr;
	t_env *env;

	(void)argc;
	(void)argv;

	//env = ms_init_env(envp);
	//	ms_env(env);

	pos = get_reds_positions(str);
	reds = extract_reds(str, pos);
		printf("Before:\n");
	curr = reds;
	while (curr)
	{
		printf("%d\n", curr->pos);
		printf("[%s][%s]\n", curr->left, curr->right);
		curr = curr->next;
	}
	printf("---------------\nAfter:\n");
	clean_reds_wings(reds);
	curr = reds;
	while (curr)
	{
		printf("%d\n", curr->pos);
		printf("[%s][%s]\n", curr->left, curr->right);
		curr = curr->next;
	}
	char *cmd = get_clean_cmd(*str, reds);
//	printf("-> %s\n", cmd);
	if (exec_reds(reds) != -1)
	{
		char **tab = ft_strsplit_del(cmd, " ");
		execve(tab[0], tab, envp);
	}
	return (0);
}
*/