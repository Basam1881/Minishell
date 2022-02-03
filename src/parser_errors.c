/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:52:23 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/03 13:53:06 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_string(int x)
{
	if (g_data.double_qoute_flag || g_data.cmdline[(x)] == '"')
		ft_putchar_fd('"', 2);
	else if (g_data.single_qoute_flag || g_data.cmdline[(x)] == '\'')
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
