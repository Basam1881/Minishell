/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ultimate_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:08:30 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/23 21:26:47 by bnaji            ###   ########.fr       */
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
void	alloc_cmd(int *i, int *old_x, int x)
{
	int	j;

	j = 0;
	if (g_data.dbl_op_f)
		g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x));
	else
		g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x + 1));
	if (!g_data.sep_cmds[*i])
		ft_exit(1);
	j = 0;
	while (*old_x < x)
	{
		if (g_data.dbl_op_f && *old_x == x - 1)
		{
			g_data.dbl_op_f = 0;
			(*old_x) += 2;
			break ;
		}
		g_data.sep_cmds[*i][j] = g_data.cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	g_data.sep_cmds[*i][j] = 0;
	(*old_x)++;
	(*i)++;
}

/**
 * This function is allocate last command for sep_cmds
 * **/
void	alloc_last_cmd(int *i, int *old_x, int *x)
{
	int	j;

	g_data.sep_cmds[*i] = (char *)malloc(sizeof(char) * (*x - *old_x + 1));
	j = 0;
	while (*old_x < *x)
	{
		g_data.sep_cmds[*i][j] = g_data.cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	g_data.sep_cmds[*i][j] = 0;
	(*i)++;
	g_data.sep_cmds[*i] = 0;
}

/**
 * This function is to get sep_cmds from cmdline
 **/
void	sep_cmds_creator(void)
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
			alloc_cmd(&i, &old_x, x);
		x++;
	}
	alloc_last_cmd(&i, &old_x, &x);
}

/**
 * This is the ultimate 3d split
 * Nothing to explain It's the best 
 * PEACE
 **/
void	ultimate_3d_split(void)
{
	int	x;
	int	ops_cnt;

	x = 0;
	ops_cnt = 0;
	if (!*g_data.cmdline || empty_cmd_checker())
		return ;
	while (g_data.cmdline[x])
	{
		qoutes_checker_3d(&x);
		operators_checker(&x, &ops_cnt, 0);
		x++;
	}
	g_data.cmd = (char ***)malloc(sizeof(char **) * (ops_cnt + 2));
	g_data.sep_cmds = (char **)malloc(sizeof(char *) * (ops_cnt + 2));
	g_data.ops_array = (int *)malloc(sizeof(int) * (ops_cnt + 1));
	if (!g_data.cmd || !g_data.sep_cmds)
		ft_exit(1);
	g_data.op_cnt = 0;
	sep_cmds_creator();
	g_data.n = 0;
	while (g_data.n < ops_cnt + 1)
		g_data.cmd[g_data.n++] = cmd_split();
	g_data.cmd[g_data.n] = 0;
	g_data.n = 0;
}
