/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:20:16 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/30 11:50:26 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function will check for any pipes or redirections and call the crosponding fucntions to handle them.
	**********REMINDER : FIX DOUBLE INPUT (<<) (CURRENTLY IT WORKS ON LAPTOP BUT NOT ON 42 LABS)**********
*/
int	check_op(int *i, int *j)
{
	int	n;
	int	error_flag;
	int	k;

	error_flag = 0;
	k = 0;
	env_exit(*i);
	if (g_data.ops_array[*j] == 1)
		pipe_write("write", i, j);
	else if (is_redir(*j))
	{
		while (is_redir(*j) && *j < g_data.op_cnt)
		{
			k++;
			env_exit(*i + k);
			if (error_flag)
			{
				if (g_data.ops_array[*j] == 6)
					handle_redirection(g_data.ops_array[*j], *j);
				(*j)++;
				continue ;
			}
			n = 1;
			if (g_data.ops_array[*j] != 6)
			{
				if (handle_wild_card(*j + 1) == -1)
				{
					error_flag = 1;
					continue ;
				}
			}
			if (handle_redirection(g_data.ops_array[*j], *j))
				error_flag = 1;
			while (g_data.cmd[*j + 1][n] && !error_flag)
				ft_strjoin_2d(g_data.cmd[*j + 1][n++]);
			(*j)++;
		}
		if (error_flag)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
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
	if (error_flag)
		return (1);
	return (0);
}