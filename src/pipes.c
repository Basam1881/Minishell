/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:23:38 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/17 17:10:30 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function will redirect the input source to the read side of the pipe (Only if needed !)
*/
void	pipe_read(void)
{
	if (g_data.ops_array[g_data.x - 1] == 1)
	{
		if (g_data.ops_array[g_data.x] != 1)
		{
			if (g_data.x == g_data.op_cnt)
				dup2(g_data.fdout, STDOUT_FILENO);
			if (!g_data.input_flag)
				dup2(g_data.fd[g_data.pipes][0], STDIN_FILENO);
			close(g_data.fd[g_data.pipes][0]);
		}
		else
		{
			if (!g_data.input_flag)
				dup2(g_data.fd[g_data.pipes - 1][0], STDIN_FILENO);
			close(g_data.fd[g_data.pipes - 1][0]);
		}
	}
}

/* 
	this function will redirect the output source to the write side of the pipe (Only if needed !)
*/
void	pipe_write(char *type, int *i, int *j)
{
	if (ft_strcmp(type, "write") == 0)
	{
		g_data.pipes++;
		pipe(g_data.fd[g_data.pipes]);
		dup2(g_data.fd[g_data.pipes][1], STDOUT_FILENO);
		(*j)++;
		(*i)++;
	}
	else if (ft_strcmp(type, "write2") == 0)
	{
		g_data.pipes++;
		pipe(g_data.fd[g_data.pipes]);
		if (!g_data.output_flag)
			dup2(g_data.fd[g_data.pipes][1], STDOUT_FILENO);
		g_data.x = *j;
		(*j)++;
		g_data.pipe_flag = 0;
	}
}