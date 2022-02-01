/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:12:04 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 18:13:14 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_dollar(int *x)
{
	if ((g_data.sep_cmds[g_data.n][*x] == '$' && g_data.sep_cmds[g_data
			.n][*x + 1] && g_data.sep_cmds[g_data.n][*x + 1] != ' '
				&& !g_data.single_qoute_flag && !g_data.double_qoute_flag)
			|| (g_data.sep_cmds[g_data.n][*x] == '$' && g_data.sep_cmds[g_data
			.n][*x + 1] && g_data.sep_cmds[g_data.n][*x + 1] != ' ' && g_data
			.sep_cmds[g_data.n][*x + 1] != '"' && !g_data.single_qoute_flag
				&& g_data.double_qoute_flag))
		return (1);
	return (0);
}

/**
 * It's used to set the qoutes flags either to 1 or 0, so we 
 * can tell if we are inside qoutes at the moment or not
**/
void	qoutes_checker(int *x, int *i, int *j)
{
	if ((g_data.sep_cmds[g_data.n][*x] == '\'' && g_data.single_qoute_flag)
		|| (g_data.sep_cmds[g_data.n][*x] == '"' && g_data.double_qoute_flag))
	{
		if (g_data.sep_cmds[g_data.n][*x] == '\'')
			g_data.single_qoute_flag = 0;
		else
			g_data.double_qoute_flag = 0;
	}
	else
	{
		if (is_dollar(x))
			env_checker(x, i, j);
		else if (g_data.split_flag == 2)
			g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
		if (g_data.digit_env)
		{
			g_data.digit_env = 0;
			return ;
		}
		if (g_data.split_flag)
			(*j)++;
	}
	(*x)++;
}

int	is_sep_empty(void)
{
	int	i;

	if (!*g_data.sep_cmds[g_data.n])
		return (0);
	i = 0;
	while (g_data.sep_cmds[g_data.n][i])
	{
		if (g_data.sep_cmds[g_data.n][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
