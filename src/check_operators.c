/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:20:16 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 07:59:56 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_red_error(int *j)
{
	if (g_data.error_flag)
	{
		if (g_data.ops_array[*j] == 6)
			handle_redirection(g_data.ops_array[*j], *j);
		(*j)++;
		return (1);
	}
	return (0);
}

void	check_redirections(int *i, int *j)
{
	int	n;

	while (is_redir(*j) && *j < g_data.op_cnt)
	{
		if (check_red_error(j))
			continue ;
		n = 1;
		if (g_data.ops_array[*j] != 6)
		{
			env_exit(*i + 1);
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

void	check_red_dbl(int *i, int *j)
{
	check_redirections(i, j);
	if (g_data.error_flag)
		ft_putendl_fd(strerror(errno), 2);
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

/* this function will check for any operators and 
	call the crosponding fucntions to handle them.*/
int	check_op(int *i, int *j)
{
	g_data.error_flag = 0;
	env_exit(*i);
	if (g_data.ops_array[*j] == 1)
		pipe_write("write", i, j);
	else if (is_redir(*j))
		check_red_dbl(i, j);
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
