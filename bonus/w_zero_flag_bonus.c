/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_zero_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:17:19 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/03 12:26:05 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	single_no_arg(int *x)
{
	if (!((g_data.cmdline[(*x)] == '(' && (!g_data.last_op
					|| g_data.last_op == 1 || g_data.last_op == 4
					|| g_data.last_op == 7 || g_data.last_op == 8))
			|| (g_data.cmdline[(*x)] != '(' && g_data.last_op == 9)))
	{
		if (is_op_redir(0, g_data.cmdline[(*x)], 1))
		{
			if (is_op_redir(g_data.last_op, 0, 0))
				return (unexpected_msg(*x, 1, NULL));
		}
		else
			return (unexpected_msg(*x, 1, NULL));
	}
	else if ((is_op_redir(0, g_data.cmdline[(*x)], 1)
			|| g_data.cmdline[(*x)] == '|') && g_data.last_op == 9)
		return (unexpected_msg(*x, 1, NULL));
	return (0);
}

int	single_w_zero_flag(int *x, int flag)
{
	if (g_data.cmdline[(*x)] == '(')
	{
		g_data.paren_cnt++;
		g_data.parentheses_cnt++;
	}
	else if (g_data.cmdline[(*x)] == ')')
	{
		if (!g_data.parentheses_cnt)
			return (unexpected_msg(*x, 4, LAST_PARENTH_MSG));
		g_data.parentheses_cnt--;
		g_data.paren_cnt++;
	}
	if (g_data.empty_flag)
	{
		if (g_data.cmdline[(*x)] == '(')
			return (unexpected_msg(*x, 1, NULL));
		g_data.empty_flag = 0;
	}
	else
	{
		if (single_no_arg(x))
			return (1);
	}
	ops_assigner(x, 1, &g_data.last_op, flag);
	return (0);
}

int	double_w_zero_flag(int *x, int flag)
{
	if (g_data.empty_flag)
		g_data.empty_flag = 0;
	else
	{
		if (!(g_data.last_op == 9))
		{
			if (is_op_redir(0, g_data.cmdline[(*x)], 1))
			{
				if (is_op_redir(g_data.last_op, 0, 0))
					return (unexpected_msg(*x, 1, NULL));
			}
			else
				return (unexpected_msg(*x, 2, NULL));
		}
		else
			if (is_op_redir(0, g_data.cmdline[(*x)], 1))
				return (unexpected_msg(*x, 1, NULL));
	}
	ops_assigner(x, 0, &g_data.last_op, flag);
	return (0);
}
