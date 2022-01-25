/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:02:19 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/25 18:50:23 by bnaji            ###   ########.fr       */
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

static void	ops_assigner(int *x, int is_single_op, int *var)
{
	if (is_single_op == 1)
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

int	single_w_zero_flag(int *x)
{
	if (g_data.cmdline[(*x)] == '(')
		g_data.parentheses_cnt++;
	else if (g_data.cmdline[(*x)] == ')')
	{
		if (!g_data.parentheses_cnt)
			return (unexpected_msg(*x, 4, FIRST_PARENTH_MSG));
		g_data.parentheses_cnt--;
	}
	if (g_data.empty_flag)
	{
		if (g_data.cmdline[(*x)] == '(')
			return (unexpected_msg(*x, 1, NULL));
		g_data.empty_flag = 0;
	}
	else
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
	}
	ops_assigner(x, 1, &g_data.last_op);
	return (0);
}

int	double_w_zero_flag(int *x)
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
	ops_assigner(x, 0, &g_data.last_op);
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
			ops_assigner(x, 1, &g_data.ops_array[g_data.op_cnt++]);
		else
			if (single_w_zero_flag(x))
				return (1);
	}
	else if (is_double_op(*x))
	{
		if (flag)
			ops_assigner(x, 0, &g_data.ops_array[g_data.op_cnt++]);
		else
			if (double_w_zero_flag(x))
				return (1);
		g_data.dbl_op_f = 1;
		(*x)++;
	}
	(*ops_cnt)++;
	return (0);
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
 * * TODO: throw an error if there is nothing in between operators
 * * TODO: throw an error if there is nothing after operator
 * * TODO: accept nothing before first redirection in a command
 * * TODO: check the character after the operators and throw an error if the combination is wrong
 * TODO: Cover the previous conditions for quotes and without them
 * TODO: exit with 1 from these errors
 * TODO: check the permission of the file before using it
 * TODO: you should be able to create files with symbols even without qoutes (you need to remove the else if condition that check if it's a alpha, digit or _)
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
	{
		if (!flag)
		{
			if (g_data.last_op == 9)
				return (unexpected_msg(*x, 3, NULL));
			g_data.empty_flag = 1;
		}
	}
	return (0);
}
