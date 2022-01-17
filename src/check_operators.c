/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:20:16 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/17 06:26:24 by mal-guna         ###   ########.fr       */
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
	int error_flag;

	error_flag = 0;
	if (g_data.ops_array[*j] == 1)
		pipe_write("write", i, j);
	else if (g_data.ops_array[*j] == 2 || g_data.ops_array[*j] == 3 || g_data.ops_array[*j] == 5 || g_data.ops_array[*j] == 6)
	{
		while (g_data.ops_array[*j] != 1 && *j < g_data.op_cnt)
		{
			if(error_flag)
			{
				if(g_data.ops_array[*j] == 6)
				{	
					handle_redirection(g_data.ops_array[*j], *j);
				}
				(*j)++;
				continue;
			}
			n = 1;
			if(g_data.ops_array[*j] != 6)
			{
				if (handle_wild_card(*j + 1) == -1)
				{
					error_flag = 1;
					continue;
				}
			}
			if (handle_redirection(g_data.ops_array[*j], *j))
			{
				error_flag = 1;
			}
			while (g_data.cmd[*j + 1][n] && !error_flag)
			{
				ft_strjoin_2d(g_data.cmd[*j + 1][n]);
				n++;
			}
			(*j)++;
		}
		if(error_flag)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
		}
		*i = *j + 1;
		if (g_data.ops_array[*j] == 1)
			g_data.pipe_flag = 1;
	}
	else
		(*i)++;
	if(error_flag)
		return (1);
	return (0);
}