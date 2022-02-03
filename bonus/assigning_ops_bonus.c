/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigning_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:37:39 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/03 19:11:05 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	assign_open_paren(int *x, int *var, int flag)
{
	if (flag == 1)
	{
		if (!*x || g_data.cmdline[*x - 1] != '(')
			g_data.paren_array[g_data.paren_cnt] = 1;
		else
			g_data.paren_array[g_data.paren_cnt] = -1;
		g_data.paren_cnt++;
	}
	*var = 8;
}

static int	assign_close_paren(int *x, int *var, int flag)
{
	int	i;

	if (flag)
	{
		g_data.paren_array[g_data.paren_cnt] = 2;
		i = 0;
		while (g_data.paren_cnt > 2 && g_data.paren_array[g_data
				.paren_cnt - i] == 2)
			i++;
		i--;
		if (g_data.cmdline[*x - 1] == ')' && g_data
			.paren_array[g_data.paren_cnt - i * 2] == -1)
		{
			g_data.exit_status = 1;
			g_data.paren_array[g_data.paren_cnt - (i * 2) - 1] = -2;
			g_data.paren_array[g_data.paren_cnt - 1] = 3;
		}
		g_data.paren_cnt++;
	}
	*var = 9;
	return (0);
}

static int	assign_paren(int *x, int *var, int flag)
{
	if (g_data.cmdline[(*x)] == '(')
		assign_open_paren(x, var, flag);
	else if (g_data.cmdline[(*x)] == ')')
		if (assign_close_paren(x, var, flag))
			return (1);
	return (0);
}

int	ops_assigner(int *x, int is_single, int *var, int flag)
{
	if (is_single == 1)
	{
		if (g_data.cmdline[(*x)] == '|')
			*var = 1;
		else if (g_data.cmdline[(*x)] == '>')
			*var = 2;
		else if (g_data.cmdline[(*x)] == '<')
			*var = 3;
		else
			if (assign_paren(x, var, flag))
				return (1);
	}
	else
	{
		if (g_data.cmdline[(*x)] == '|')
			*var = 4;
		else if (g_data.cmdline[(*x)] == '>')
			*var = 5;
		else if (g_data.cmdline[(*x)] == '<')
			*var = 6;
		else if (g_data.cmdline[(*x)] == '&')
			*var = 7;
	}
	return (0);
}
