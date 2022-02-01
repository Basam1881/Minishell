/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:20:16 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/01 20:58:00 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function will check for any pipes or redirections and call the crosponding fucntions to handle them.
	**********REMINDER : FIX DOUBLE INPUT (<<) (CURRENTLY IT WORKS ON LAPTOP BUT NOT ON 42 LABS)**********
*/

void	check_redirections(int *i, int *j)
{
	int n;
	int k;

	k = 1;
	while (is_redir(*j) && *j < g_data.op_cnt)
	{
		if (g_data.error_flag)
		{
			if (g_data.ops_array[*j] == 6)
				handle_redirection(g_data.ops_array[*j], *j);
			(*j)++;
			continue ;
		}
		n = 1;
		if (g_data.ops_array[*j] != 6)
		{
			env_exit(*i + k);
			if (handle_wild_card(*j + 1) == -1)
			{
				g_data.error_flag = 1;
				continue ;
			}
		}
		if (handle_redirection(g_data.ops_array[*j], *j))
			g_data.error_flag = 1;
		while (g_data.cmd[*j + 1][n] && !(g_data.error_flag))
			ft_strjoin_2d(g_data.cmd[*j + 1][n++]);
		(*j)++;
	}
}

int	check_op(int *i, int *j)
{
	g_data.error_flag = 0;
	env_exit(*i);
	if (g_data.ops_array[*j] == 1)
		pipe_write("write", i, j);
	else if (is_redir(*j))
	{
		check_redirections(i, j);
		if (g_data.error_flag)
		{
			ft_putendl_fd(strerror(errno), 2);
		}
		*i = *j + 1;
		if (g_data.ops_array[*j] == 1)
			g_data.pipe_flag = 1;
		else if (g_data.ops_array[*j] == 4)
		{
			(*j)++;
			g_data.is_dbl_pipe = 1;
		}
		else if (g_data.ops_array[*j] == 7)
		{
			(*j)++;
			g_data.is_dbl_and = 1;
		}
		else if (g_data.ops_array[*j] == 9)
			g_data.sub_exit_flag = 1;
	}
	else if (g_data.ops_array[*j] == 4)
	{
		g_data.is_dbl_pipe = 1;
		(*i)++;
		(*j)++;
	}
	else if (g_data.ops_array[*j] == 7)
	{
		g_data.is_dbl_and = 1;
		(*i)++;
		(*j)++;
	}
	else if (!g_data.ops_array[*j])
		(*i)++;
	if (g_data.error_flag)
		return (1);
	return (0);
}
