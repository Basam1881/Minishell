/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:31:54 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/02 14:17:30 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strlen_to_space(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]))
		return (-1);
	while (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
		i++;
	return (i);
}

static void	no_env_in_no_qoutes(char *new_s, int *i, int *j, int *x)
{
	if (!new_s)
	{
		if (!g_data.double_qoute_flag && !g_data.single_qoute_flag && (!g_data.n || g_data
				.sep_cmds[g_data.n][*x - 1] == ' ')
				&& (g_data.sep_cmds[g_data.n][*x + ft_strlen_to_space(&g_data
				.sep_cmds[g_data.n][*x + 1]) + 1] == ' ' || !g_data
				.sep_cmds[g_data.n][*x + ft_strlen_to_space(&g_data
				.sep_cmds[g_data.n][*x + 1]) + 1]))
		{
			(*i)--;
			g_data.no_env_arg_flag = 1;
		}
		else
			(*j)--;
	}
}

static int	special_non_existent_env(int old_len, int *x, int *i, int *j)
{
	if (!old_len)
	{
		if ((!g_data.double_qoute_flag && !g_data.single_qoute_flag)
			&& (g_data.sep_cmds[g_data.n][*x + 1] == '\''
			|| g_data.sep_cmds[g_data.n][*x + 1] == '"'))
		{
			(*x)++;
			g_data.digit_env = 1;
		}
		else if (g_data.split_flag == 2)
			g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
		return (1);
	}
	else if (old_len == -1)
	{
		(*x) += 2;
		g_data.digit_env = 1;
		return (1);
	}
	return (0);
}

static void	replace_s_w_env_val(int *i, int *j, char *new_s)
{
	int	n;
	int	new_len;

	if (g_data.split_flag)
	{
		new_len = ft_strlen(new_s);
		if (g_data.split_flag == 1)
			*j += new_len;
		else
		{
			n = 0;
			while (n < new_len)
			{
				g_data.cmd[g_data.n][*i][(*j)++] = new_s[n];
				n++;
			}
		}
		(*j)--;
	}
}

/**
**/
void	env_checker(int *x, int *i, int *j)
{
	int		old_len;
	char	*old_s;
	char	*new_s;

	if (g_data.n)
	{
		if (g_data.ops_array[g_data.n - 1] == 6)
		{
			if (g_data.split_flag == 2)
				g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
			return ;
		}	
	}
	old_len = ft_strlen_to_space(&g_data.sep_cmds[g_data.n][*x + 1]);
	if (special_non_existent_env(old_len, x, i, j))
		return ;
	old_s = ft_substr(&g_data.sep_cmds[g_data.n][*x + 1], 0, old_len);
	new_s = get_expnd_val(old_s);
	free (old_s);
	if (new_s)
		replace_s_w_env_val(i, j, new_s);
	else
		no_env_in_no_qoutes(new_s, i, j, x);
	free(new_s);
	(*x) += old_len;
}
