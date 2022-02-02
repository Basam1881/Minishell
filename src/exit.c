/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/02 13:01:56 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_big_g_data(void)
{
	int	i;
	int	j;

	i = 0;
	if (g_data.cmd)
	{
		while (g_data.cmd[i])
		{
			j = 0;
			while (g_data.cmd[i][j])
			{
				free (g_data.cmd[i][j]);
				j++;
			}
			free (g_data.cmd[i++]);
		}
		free (g_data.cmd);
	}
	i = 0;
	if (g_data.sep_cmds)
	{
		while (g_data.sep_cmds[i])
			free (g_data.sep_cmds[i++]);
		free (g_data.sep_cmds);
	}
}

void	free_all(void)
{
	if (!g_data.cmdline)
		return ;
	if (*g_data.cmdline)
		free(g_data.cmdline);
	free_big_g_data();
	if (g_data.cmd_path)
		free(g_data.cmd_path);
	if (g_data.ops_array)
		free(g_data.ops_array);
	if (g_data.star_array)
		free(g_data.star_array);
	if (g_data.q_array)
		free(g_data.q_array);
	if (g_data.fd)
	{
		free(g_data.fd);
		g_data.fd = NULL;
	}
	reset();
}

void	error_printer(void)
{
	free_all();
	ft_putstr_fd("BNM bash: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	g_data.exit_status = 1;
}

/**
 * TODO: check the errno for common functions like malloc, read, \
 * 		TODO: write and return the errno for them and print their \
 * 		TODO: error messages from here
 */
void	exit_shell(int n)
{
	free_all();
	clear_history();
	if (g_data.environ)
		free_2d(&g_data.environ);
	exit(n);
}
