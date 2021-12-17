/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:02:19 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/17 02:20:39 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ops_assigner(int *x, int flag)
{
	if (flag == 1)
	{
		if (g_data.cmdline[(*x)] == '|')
			g_data.ops_array[g_data.op_cnt] = 1;
		else if (g_data.cmdline[(*x)] == '>')
			g_data.ops_array[g_data.op_cnt] = 2;
		else if (g_data.cmdline[(*x)] == '<')
			g_data.ops_array[g_data.op_cnt] = 3;
		g_data.op_cnt++;
	}
	else
	{
		if (g_data.cmdline[(*x)] == '|')
			g_data.ops_array[g_data.op_cnt] = 4;
		else if (g_data.cmdline[(*x)] == '>')
			g_data.ops_array[g_data.op_cnt] = 5;
		else if (g_data.cmdline[(*x)] == '<')
			g_data.ops_array[g_data.op_cnt] = 6;
		else if (g_data.cmdline[(*x)] == '&')
			g_data.ops_array[g_data.op_cnt] = 7;
		g_data.op_cnt++;
	}
}

/**
 * This function is to check the operators
 * there operators are represented in numbers as following
 * 		1 = |
 *  	2 = >
 * 		3 = <
 * 		4 = ||
 * 		5 = >>
 * 		6 = <<
 * 		7 = &&
 **/
void	operators_checker(int *x, int *ops_cnt, int flag)
{
	if (!g_data.single_qoute_flag && !g_data.double_qoute_flag)
	{
		if ((g_data.cmdline[(*x)] == '|' && g_data.cmdline[(*x) + 1] != '|')
			|| (g_data.cmdline[(*x)] == '>' && g_data.cmdline[(*x) + 1] != '>')
			|| (g_data.cmdline[(*x)] == '<' && g_data.cmdline[(*x) + 1] != '<'))
		{
			if (flag)
				ops_assigner(x, 1);
			(*ops_cnt)++;
		}
		else if ((g_data.cmdline[(*x)] == '|' && g_data.cmdline[(*x) + 1] == '|')
			|| (g_data.cmdline[(*x)] == '>' && g_data.cmdline[(*x) + 1] == '>')
			|| (g_data.cmdline[(*x)] == '<' && g_data.cmdline[(*x) + 1] == '<')
			|| (g_data.cmdline[(*x)] == '&' && g_data.cmdline[(*x) + 1] == '&'))
		{
			if (flag)
				ops_assigner(x, 0);
			g_data.dbl_op_f = 1;
			(*ops_cnt)++;
			(*x)++;
		}
	}
}
