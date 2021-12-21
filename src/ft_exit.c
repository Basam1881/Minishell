/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 08:48:02 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/20 00:19:13 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_exit(int i)
{
	int	n;

	if (!g_data.cmd[i][1])
	{
		printf("%s\n", NO_COLOR);
		ft_exit(g_data.exit_status);
	}
	else if (g_data.cmd[i][1] && !g_data.cmd[i][2])
	{
		printf("%s\n", NO_COLOR);
		n = ft_atoi(g_data.cmd[i][1]);
		ft_exit(n);
	}
	else
	{
		printf("exit: too many arguments\n");
		g_data.exit_status = 1;
	}
}
