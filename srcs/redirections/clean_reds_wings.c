#include "mysh.h"

void clean_right(char **right)
{
	char *tmp;
	int vc;

	vc = valid_right_chars(*right);
	tmp = ft_strsub(*right, 0, vc);
	if (*right)
		free(*right);
	*right = tmp;
}

void clean_left(char **left, int type)
{
	char *tmp;
	int vc;

	vc = valid_left_chars(*left, type);
	tmp = ft_strsub(*left, ft_strlen(*left) - vc, vc);
	if (*left)
		free(*left);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		*left = NULL;
	}
	else
		*left = tmp;
}

void print_red(t_red *red)
{
	ft_putstr_fd(red->o_left, 2);
	if (red->type == RS)
		ft_putstr_fd(">", 2);
	else if (red->type == LS)
		ft_putstr_fd("<", 2);
	else if (red->type == RD)
		ft_putstr_fd(">>", 2);
	else if (red->type == LD)
		ft_putstr_fd("<<", 2);
	ft_putstr_fd(red->o_right, 2);
}

int is_valid_red(t_red *red)
{
	if (ft_strlen(red->left) == 1 && red->left[0] == '&')
	{
		if (red->right[0] == '&')
		{
			ft_putstr("ambiguous redirect: ");
			print_red(red);
			ft_putchar('\n');
			return (0);
		}
	}
	return (1);
}

void clean_reds_wings(t_red *reds)
{
	t_red	*red;
	char	*tmp;

	red = reds;
	while (red)
	{
		red->o_left = ft_strdup(red->left);
		red->o_right = ft_strdup(red->right);
		clean_left(&(red->left), red->type);
		if (red->left != NULL)
		{
			tmp = ft_strdup(red->left);
			free(red->left);
			red->left = ms_expand_arg(tmp);
			free(tmp);
		}
		clean_right(&(red->right));
		if (red->right != NULL)
		{
			tmp = ft_strdup(red->right);
			free(red->right);
			red->right = ms_expand_arg(tmp);
			free(tmp);
		}
		if (red->type != RD && red->type != LS)
			is_valid_red(red);
		red = red->next;
	}
}