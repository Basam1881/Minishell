/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:25:55 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 16:05:56 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_echo_args(int *i, int *j, int *n_flag)
{
	while (g_data.cmd[g_data.y][*j][0] == '-')
	{
		*i = 1;
		while (g_data.cmd[g_data.y][*j][*i] == 'n')
			(*i)++;
		if (*i > 1 && !g_data.cmd[g_data.y][*j][*i])
		{
			*n_flag = 1;
			(*j)++;
		}
		else
			break ;
	}
}

void	ft_echo(void)
{
	int	n_flag;
	int	j;
	int	i;

	n_flag = 0;
	if (!g_data.cmd[g_data.y][1])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	j = 1;
	print_echo_args(&i, &j, &n_flag);
	while (g_data.cmd[g_data.y][j])
	{
		ft_putstr_fd(g_data.cmd[g_data.y][j], 1);
		if (g_data.cmd[g_data.y][j + 1])
			ft_putchar_fd(' ', 1);
		j++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_data.exit_status = 0;
}
