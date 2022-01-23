/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ultimate_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:08:30 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/23 15:59:49 by bnaji            ###   ########.fr       */
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

/**
 * This function is allocate each command for sep_cmds
 **/
int	alloc_cmd(int *i, int *old_x, int x)
{
	int	j;

	if (g_data.dbl_op_f)
		g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x));
	else
		g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x + 1));
	if (!g_data.sep_cmds[*i])
	{
		failed_sep_cmds(*i);
		return (1);
	}
	j = 0;
	while (*old_x < x)
	{
		if (g_data.dbl_op_f && *old_x == x - 1)
		{
			g_data.dbl_op_f = 0;
			(*old_x)++;
			break ;
		}
		g_data.sep_cmds[*i][j] = g_data.cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	g_data.sep_cmds[*i][j] = 0;
	(*old_x)++;
	(*i)++;
	g_data.dbl_op_f = 0;
	return (0);
}

/**
 * This function is allocate last command for sep_cmds
 * **/
int	alloc_last_cmd(int *i, int *old_x, int *x)
{
	int	j;

	g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (*x - *old_x + 1));
	if (!g_data.sep_cmds[*i])
	{
		failed_sep_cmds(*i);
		return (1);
	}
	j = 0;
	while (*old_x < *x)
	{
		g_data.sep_cmds[*i][j] = g_data.cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	g_data.sep_cmds[*i][j] = 0;
	(*i)++;
	g_data.sep_cmds[*i] = NULL;
	g_data.dbl_op_f = 0;
	return (0);
}

/**
 * The star_assigner() function allocates and assign an array of flags for the wildcard (*)
**/
void	star_assigner(int x, int flag)
{
	if (!flag)
	{
		if (g_data.cmdline[x] == '*')
			g_data.star_cnt++;
	}
	else
	{
		if (g_data.cmdline[x] == '*')
		{
			if (g_data.single_qoute_flag || g_data.double_qoute_flag)
				g_data.star_array[g_data.star_cnt++] = -1;
			else
				g_data.star_array[g_data.star_cnt++] = 1;
		}
	}
}

/**
 * This function is to get sep_cmds from cmdline
 **/
int	sep_cmds_creator(void)
{
	int	ops_cnt;
	int	i;
	int	old_x;
	int	x;

	old_x = 0;
	i = 0;
	ops_cnt = 0;
	x = 0;
	while (g_data.cmdline[x])
	{
		qoutes_checker_3d(&x);
		operators_checker(&x, &ops_cnt, 1);
		g_data.ops_array[g_data.op_cnt] = '\0';
		if (ops_cnt != i)
		{
			if (alloc_cmd(&i, &old_x, x))
				return (1);
		}
		star_assigner(x, 1);
		x++;
	}
	if (alloc_last_cmd(&i, &old_x, &x))
		return (1);
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

	x = 0;
	ops_cnt = 0;
	if (!*g_data.cmdline || empty_cmd_checker())
		return (1);
	while (g_data.cmdline[x])
	{
		qoutes_checker_3d(&x);
		if (operators_checker(&x, &ops_cnt, 0))
			return (1);
		star_assigner(x, 0);
		x++;
	}
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
	if (!g_data.cmd || !g_data.sep_cmds
		|| !g_data.ops_array || !g_data.star_array)
	{
		error_printer();
		return (1);
	}
	g_data.star_array[g_data.star_cnt] = -0;
	g_data.star_cnt = 0;
	g_data.op_cnt = 0;
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
	return (0);
}
