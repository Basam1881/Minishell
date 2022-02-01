/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ultimate_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:08:30 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 19:25:03 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function is to check the qoutes for the 3d array split
 **/
void	qoutes_checker_3d(int *x)
{
	if ((g_data.cmdline[*x] == '\'' || g_data.cmdline[*x] == '"')
		&& !g_data.single_qoute_flag && !g_data.double_qoute_flag)
	{
		if (g_data.cmdline[*x] == '\'')
			g_data.single_qoute_flag = 1;
		else
			g_data.double_qoute_flag = 1;
		(*x)++;
	}
	if ((g_data.cmdline[*x] == '\'' && g_data.single_qoute_flag)
		|| (g_data.cmdline[*x] == '"' && g_data.double_qoute_flag))
	{
		if (g_data.cmdline[*x] == '\'')
			g_data.single_qoute_flag = 0;
		else
			g_data.double_qoute_flag = 0;
	}
}

static int	ultimate_helper(int x, int ops_cnt)
{
	if (ops_cnt && !g_data.empty_flag && g_data.last_op != 9)
		return (unexpected_msg(x, 4, NEWLINE_MSG));
	else if (g_data.parentheses_cnt)
		return (unexpected_msg(x, 4, FIRST_PARENTH_MSG));
	else if (g_data.single_qoute_flag)
		return (unexpected_msg(x, 4, UNCLOSED_SINGLE));
	else if (g_data.double_qoute_flag)
		return (unexpected_msg(x, 4, UNCLOSED_DOUBLE));
	g_data.empty_flag = 0;
	g_data.cmd = (char ***)malloc(sizeof(char **) * (ops_cnt + 2));
	g_data.sep_cmds = (char **)malloc(sizeof(char *) * (ops_cnt + 2));
	g_data.ops_array = (int *)malloc(sizeof(int) * (ops_cnt + 1));
	g_data.star_array = (int *)malloc(sizeof(int) * (g_data.star_cnt + 1));
	g_data.q_array = (int *)malloc(sizeof(int) * (g_data.question_cnt + 1));
	if (!g_data.cmd || !g_data.sep_cmds
		|| !g_data.ops_array || !g_data.star_array)
	{
		error_printer();
		return (1);
	}
	g_data.star_array[g_data.star_cnt] = 0;
	g_data.star_cnt = 0;
	g_data.question_cnt = 0;
	g_data.op_cnt = 0;
	return (0);
}

static int	check_to_store(int *x, int *ops_cnt)
{
	*x = 0;
	*ops_cnt = 0;
	if (!*g_data.cmdline || empty_cmd_checker())
		return (1);
	while (g_data.cmdline[*x])
	{
		qoutes_checker_3d(x);
		if (operators_checker(x, ops_cnt, 0))
			return (1);
		q_and_star_assigner(*x, 0);
		(*x)++;
	}
	return (0);
}

/**
 * This is the ultimate 3d split
 * Nothing to explain It's the best
 * PEACE
 **/
int	ultimate_3d_split(void)
{
	int	x;
	int	ops_cnt;

	check_to_store(&x, &ops_cnt);
	if (ultimate_helper(x, ops_cnt))
		return (1);
	if (sep_cmds_creator())
		return (1);
	g_data.n = 0;
	while (g_data.n < ops_cnt + 1)
	{
		g_data.cmd[g_data.n] = cmd_split();
		if (!g_data.cmd[g_data.n])
			return (1);
		g_data.n++;
	}
	g_data.cmd[g_data.n] = NULL;
	g_data.n = 0;
	g_data.parentheses_cnt = 0;
	g_data.question_cnt = 0;
	return (0);
}
