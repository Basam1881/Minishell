/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 08:48:02 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/30 10:53:30 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(void)
{
	int	n;

	if (!g_data.cmd[g_data.y][1])
	{
		printf("%s\n", NO_COLOR);
		exit_shell(g_data.exit_status);
	}
	else if (g_data.cmd[g_data.y][1] && !g_data.cmd[g_data.y][2])
	{
		printf("%s\n", NO_COLOR);
		n = ft_atoi(g_data.cmd[g_data.y][1]);
		exit_shell(n);
	}
	else
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_data.exit_status = 1;
	}
}