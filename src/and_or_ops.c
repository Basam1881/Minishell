/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:08:53 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/31 22:11:59 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_and_op(int *i, int *j)
{
	if (g_data.exit_status)
	{
		while (1)
		{
			if (g_data.ops_array[*j] == 8)
			{
				g_data.parentheses_cnt++;
				g_data.inside_parentheses_flag = 1;
			}
			else if (g_data.ops_array[*j] == 9)
			{
				g_data.parentheses_cnt--;
				g_data.inside_parentheses_flag = 0;
				if (g_data.was_child && !g_data.parentheses_cnt)
				{
					g_data.sub_exit_flag = 1;
					break ;
				}
			}
			else if ((!g_data.parentheses_cnt || (g_data.parentheses_cnt == 1
						&& g_data.was_child && !g_data.inside_parentheses_flag))
				&& (g_data.ops_array[*j] == 4 || !g_data.ops_array[*j]))
			{
				if (g_data.ops_array[*j])
					(*j)++;
				(*i)++;
				break ;
			}
			(*j)++;
			(*i)++;
		}
		g_data.inside_parentheses_flag = 0;
	}
	g_data.is_dbl_and = 0;
}

void	check_or_op(int *i, int *j)
{
	if (!g_data.exit_status)
	{
		while (1)
		{
			if (g_data.ops_array[*j] == 8)
			{
				g_data.parentheses_cnt++;
				g_data.inside_parentheses_flag = 1;
			}
			else if (g_data.ops_array[*j] == 9)
			{
				g_data.parentheses_cnt--;
				g_data.inside_parentheses_flag = 0;
				if (g_data.was_child && !g_data.parentheses_cnt)
				{
					g_data.sub_exit_flag = 1;
					break ;
				}
			}
			else if ((!g_data.parentheses_cnt || (g_data.parentheses_cnt == 1
						&& g_data.was_child && !g_data.inside_parentheses_flag))
				&& (g_data.ops_array[*j] == 7 || !g_data.ops_array[*j]))
			{
				if (g_data.ops_array[*j])
					(*j)++;
				(*i)++;
				break ;
			}
			(*j)++;
			(*i)++;
		}
		g_data.inside_parentheses_flag = 0;
	}
	g_data.is_dbl_pipe = 0;
}
