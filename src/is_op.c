/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:11:00 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/03 12:44:52 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_qoutes(int x, int flag)
{
	if (!flag)
	{
		if (g_data.last_op == 9)
			return (unexpected_msg(x, 3, NULL));
		g_data.empty_flag = 1;
	}
	return (0);
}

/**
 * * This function is not used anywhere yet but 
 * * it could help antime to shorten the code
**/
int	is_op_redir(int op, char op_c, int flag)
{
	if (!flag)
	{
		if (op == 2 || op == 3 || op == 5 || op == 6)
			return (1);
	}
	else
	{
		if (op_c == '>' || op_c == '<')
			return (1);
	}
	return (0);
}

int	is_single_op(int x)
{
	if ((g_data.cmdline[(x)] == '|' && g_data.cmdline[(x) + 1] != '|')
		|| (g_data.cmdline[(x)] == '>' && g_data.cmdline[(x) + 1] != '>')
		|| (g_data.cmdline[(x)] == '<' && g_data.cmdline[(x) + 1] != '<')
		|| g_data.cmdline[(x)] == '(' || g_data.cmdline[(x)] == ')')
		return (1);
	return (0);
}

int	is_double_op(int x)
{
	if ((g_data.cmdline[(x)] == '|' && g_data.cmdline[(x) + 1] == '|')
		|| (g_data.cmdline[(x)] == '>' && g_data.cmdline[(x) + 1] == '>')
		|| (g_data.cmdline[(x)] == '<' && g_data.cmdline[(x) + 1] == '<')
		|| (g_data.cmdline[(x)] == '&' && g_data.cmdline[(x) + 1] == '&'))
		return (1);
	return (0);
}

int	is_op(int *x, int *ops_cnt, int flag)
{
	if (is_single_op(*x))
	{
		if (flag)
		{
			if (ops_assigner(x, 1, &g_data.ops_array[g_data.op_cnt++], flag))
				return (1);
		}
		else
			if (single_w_zero_flag(x, flag))
				return (1);
	}
	else if (is_double_op(*x))
	{
		if (flag)
			ops_assigner(x, 0, &g_data.ops_array[g_data.op_cnt++], flag);
		else
			if (double_w_zero_flag(x, flag))
				return (1);
		g_data.dbl_op_f = 1;
		(*x)++;
	}
	(*ops_cnt)++;
	return (0);
}
