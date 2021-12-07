/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/07 15:33:16 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
void	failed_split(int n)
{
	while (n >= 0)
	{
		free(g_data.cmd[n]);
		n--;
	}
	free(g_data.cmd);
	free(g_data.cmdline);
	exit (1);
}

void	error(int n)
{
	int	i;

	i = 0;
	while (g_data.cmd[i])
	{
		free(g_data.cmd[i]);
		i++;
	}
	free(g_data.cmd);
	free(g_data.cmdline);
	exit(n);
}
