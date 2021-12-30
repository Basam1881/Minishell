/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:02:19 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/30 17:40:06 by bnaji            ###   ########.fr       */
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
		if ((g_data.cmdline[(*x)] == '|' && g_data.cmdline[(*x) + 1] != '|')
			|| (g_data.cmdline[(*x)] == '>' && g_data.cmdline[(*x) + 1] != '>')
			|| (g_data.cmdline[(*x)] == '<' && g_data.cmdline[(*x) + 1] != '<'))
		{
			if (flag)
				ops_assigner(x, 1);
			else
			{
				if (g_data.empty_flag)
					g_data.empty_flag = 0;
				else
				{
					ft_putstr_fd("BNM bash: syntax error near unexpected token `", 2);
					ft_putchar_fd(g_data.cmdline[(*x)], 2);
					ft_putstr_fd("'\n", 2);
					g_data.exit_status = 1;
					return (1);
				}
			}
			(*ops_cnt)++;
		}
		else if ((g_data.cmdline[(*x)] == '|' && g_data.cmdline[(*x) + 1] == '|')
			|| (g_data.cmdline[(*x)] == '>' && g_data.cmdline[(*x) + 1] == '>')
			|| (g_data.cmdline[(*x)] == '<' && g_data.cmdline[(*x) + 1] == '<')
			|| (g_data.cmdline[(*x)] == '&' && g_data.cmdline[(*x) + 1] == '&'))
		{
			if (flag)
				ops_assigner(x, 0);
			else
			{
				if (g_data.empty_flag)
					g_data.empty_flag = 0;
				else
				{
					ft_putstr_fd("BNM bash: syntax error near unexpected token `", 2);
					ft_putchar_fd(g_data.cmdline[(*x)], 2);
					ft_putstr_fd("'\n", 2);
					return (1);
				}
			}
			g_data.dbl_op_f = 1;
			(*ops_cnt)++;
			(*x)++;
		}
		else if ((ft_isalpha(g_data.cmdline[(*x)]) || ft_isdigit(g_data.cmdline[(*x)]) || g_data.cmdline[(*x)] == '_') && !flag)
			g_data.empty_flag = 1;
		else if (!flag && !g_data.empty_flag && ((g_data.cmdline[(*x)] == '\'' && g_data.cmdline[(*x - 1)] == '\'') || (g_data.cmdline[(*x)] == '"' && g_data.cmdline[(*x - 1)] == '"')))
		{
			ft_putstr_fd("BNM bash: no such file or directory: \n", 2);
			return (1);
		}
	}
	else
		if (!flag)
			g_data.empty_flag = 1;
	return (0);
}
