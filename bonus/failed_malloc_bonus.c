/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failed_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:27:01 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 16:27:14 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
void	failed_split(int n)
{
	while (g_data.n >= 0)
	{
		while (n >= 0)
		{
			free(g_data.cmd[g_data.n][n]);
			n--;
		}
		free(g_data.cmd[g_data.n]);
		g_data.n--;
	}
	free (g_data.cmd);
	g_data.cmd = NULL;
	error_printer();
}

void	failed_sep_cmds(int n)
{
	while (n >= 0)
		free(g_data.sep_cmds[n--]);
	free(g_data.sep_cmds);
	g_data.sep_cmds = NULL;
	error_printer();
}
