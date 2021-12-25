/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/17 02:12:44 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize(void)
{
	g_data.cmdline = NULL;
	g_data.cmd = NULL;
	g_data.sep_cmds = NULL;
	g_data.ops_array = NULL;
	g_data.no_env_arg_flag = 0;
	g_data.double_qoute_flag = 0;
	g_data.single_qoute_flag = 0;
	g_data.dbl_op_f = 0;
	g_data.n = 0;
	g_data.op_cnt = 0;
	g_data.pipes = -1;
	g_data.pipe_flag = 0;
	g_data.output_flag = 0;
	g_data.fdout = dup(STDOUT_FILENO);
	g_data.fdin = dup(STDIN_FILENO);
}

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
void	failed_split(int n)
{
	int	i;

	i = 0;
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
	while (g_data.sep_cmds[i])
		free (g_data.sep_cmds[i++]);
	free (g_data.sep_cmds);
	free(g_data.cmdline);
	exit (1);
}

void	free_big_g_data(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (g_data.cmd)
	{
		while (g_data.cmd[i])
		{
			j = 0;
			while (g_data.cmd[i][j])
				free (g_data.cmd[i][j++]);
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
	if (!*g_data.cmdline)
	{
		free(g_data.cmdline);
		return ;
	}
	free_big_g_data();
	free(g_data.cmdline);
	if (g_data.ops_array)
		free(g_data.ops_array);
	initialize();
}

void	ft_exit(int n)
{
	free_all();
	if (n == 1)
	{
		perror("Error. (Check your malloc functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	else if (n == 2)
	{
		perror("Error. (Check your read functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	else if (n == 3)
	{
		perror("Error. (Check your write functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	exit(n);
}
