/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:08:53 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 14:09:21 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_closed_paren(void)
{
	g_data.parentheses_cnt--;
	g_data.inside_parentheses_flag = 0;
	if (g_data.was_child && !g_data.parentheses_cnt)
	{
		g_data.sub_exit_flag = 1;
		return (1);
	}
	return (0);
}

static int	check_next_valid_cmd(int *i, int *j, int op_num)
{
	if (g_data.ops_array[*j] == 8)
	{
		g_data.parentheses_cnt++;
		g_data.inside_parentheses_flag = 1;
	}
	else if (g_data.ops_array[*j] == 9)
	{
		if (is_closed_paren())
			return (1);
	}
	else if ((!g_data.parentheses_cnt || (g_data.parentheses_cnt == 1
				&& g_data.was_child && !g_data.inside_parentheses_flag))
		&& (g_data.ops_array[*j] == op_num || !g_data.ops_array[*j]))
	{
		if (g_data.ops_array[*j])
			(*j)++;
		(*i)++;
		return (1);
	}
	(*j)++;
	(*i)++;
	return (0);
}

void	check_and_op(int *i, int *j)
{
	if (g_data.exit_status)
	{
		while (1)
			if (check_next_valid_cmd(i, j, 4))
				break ;
		g_data.inside_parentheses_flag = 0;
	}
	g_data.is_dbl_and = 0;
}

void	check_or_op(int *i, int *j)
{
	if (!g_data.exit_status)
	{
		while (1)
			if (check_next_valid_cmd(i, j, 7))
				break ;
		g_data.inside_parentheses_flag = 0;
	}
	g_data.is_dbl_pipe = 0;
}
