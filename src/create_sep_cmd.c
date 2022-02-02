/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sep_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:20:13 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/02 10:05:14 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	alloc_cmd_helper(int *i, int j, int *old_x)
{
	g_data.sep_cmds[*i][j] = 0;
	(*old_x)++;
	(*i)++;
	g_data.dbl_op_f = 0;
	return (0);
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
	return (alloc_cmd_helper(i, j, old_x));
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
	g_data.dbl_op_f = 0;
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
		q_and_star_assigner(x++, 1);
	}
	if (alloc_last_cmd(&i, &old_x, &x))
		return (1);
	return (0);
}
