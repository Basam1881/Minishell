/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:02:19 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 17:59:05 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	empty_cmd_checker(void)
{
	int	i;

	i = 0;
	if (!*g_data.cmdline)
		return (1);
	while (g_data.cmdline[i] == ' ')
		i++;
	if (!g_data.cmdline[i])
		return (1);
	return (0);
}

void	ops_assigner(int *x, int is_single, int *var)
{
	if (is_single == 1)
	{
		if (g_data.cmdline[(*x)] == '|')
			*var = 1;
		else if (g_data.cmdline[(*x)] == '>')
			*var = 2;
		else if (g_data.cmdline[(*x)] == '<')
			*var = 3;
		else if (g_data.cmdline[(*x)] == '(')
			*var = 8;
		else if (g_data.cmdline[(*x)] == ')')
			*var = 9;
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
}

void	print_error_string(int x)
{
	if (g_data.double_qoute_flag)
		ft_putchar_fd('"', 2);
	else if (g_data.single_qoute_flag)
		ft_putchar_fd('\'', 2);
	while (g_data.cmdline[(x)])
	{
		if (g_data.cmdline[(x)] == ' ' && !g_data.double_qoute_flag
			&& !g_data.single_qoute_flag)
			break ;
		if (g_data.cmdline[(x)] == '"')
		{
			if (g_data.double_qoute_flag)
				g_data.double_qoute_flag = 0;
			else
				g_data.double_qoute_flag = 1;
		}
		if (g_data.cmdline[(x)] == '\'')
		{
			if (g_data.single_qoute_flag)
				g_data.single_qoute_flag = 0;
			else
				g_data.single_qoute_flag = 1;
		}
		ft_putchar_fd(g_data.cmdline[(x++)], 2);
	}
}

int	unexpected_msg(int x, int flag, char *s)
{
	if (flag != 4)
	{
		ft_putstr_fd("BNM bash: syntax error near unexpected token `", 2);
		if (flag == 1 || flag == 2)
			ft_putchar_fd(g_data.cmdline[(x)], 2);
		else if (flag == 3)
			print_error_string(x);
		if (flag == 2)
			ft_putchar_fd(g_data.cmdline[(x) + 1], 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putendl_fd(s, 2);
	g_data.exit_status = 258;
	return (1);
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
 * 		8 = (
 * 		9 = )
 **/
int	operators_checker(int *x, int *ops_cnt, int flag)
{
	if (!g_data.single_qoute_flag && !g_data.double_qoute_flag)
	{
		if (is_single_op(*x) || is_double_op(*x))
		{
			if (is_op(x, ops_cnt, flag))
				return (1);
		}
		else if (g_data.cmdline[(*x)] != ' ')
		{
			if (!flag)
			{
				if (g_data.last_op == 9)
					return (unexpected_msg(*x, 3, NULL));
				g_data.empty_flag = 1;
			}
		}
	}
	else
		return (is_in_qoutes(*x, flag));
	return (0);
}
