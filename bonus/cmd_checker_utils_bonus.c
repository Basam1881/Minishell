/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:38:57 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/03 19:22:17 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int code, int i)
{
	if (code == 2)
	{
		ft_putstr_fd("BNM bash: ", 2);
		ft_putstr_fd(g_data.cmd[i][0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (code == 3)
	{
		ft_putstr_fd("BNM bash: ", 2);
		ft_putstr_fd(g_data.cmd[i][0], 2);
		ft_putendl_fd(": command not found", 2);
	}
}

int	ignore_wild_card(void)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	if (!g_data.cmd[g_data.y][0])
		return (0);
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "export"))
		|| (!(ft_strcmp(g_data.cmd[g_data.y][0], "unset")))
		|| (!(ft_strcmp(g_data.cmd[g_data.y][0], "env"))))
	{
		while (g_data.cmd[g_data.y][j])
		{
			while (g_data.cmd[g_data.y][j][k])
			{
				if (g_data.cmd[g_data.y][j][k] == '*')
					g_data.star_index_temp++;
				k++;
			}
			k = 0;
			j++;
		}
		return (1);
	}
	return (0);
}

int	setup_for_command(int *i, int *j, int *error_flag)
{
	g_data.y = *i;
	g_data.x = *j;
	g_data.output_flag = 0;
	g_data.input_flag = 0;
	g_data.is_path_flag = 0;
	g_data.p_flag = 0;
	*error_flag = 0;
	check_parentheses(i, j);
	if (!g_data.cmd[*i])
		return (1);
	if (!(ignore_wild_card()))
		handle_wild_card(*i);
	if (check_op(i, j))
	{
		*error_flag = 1;
		g_data.exit_status = 1;
	}
	return (0);
}

void	setup_operators(int *i, int *j, int error_flag)
{
	cmd_filter(g_data.y);
	if (g_data.y != 0)
		pipe_read();
	if (g_data.pipe_flag == 1)
		pipe_write("write2", i, j);
	if (!error_flag)
		handle_cmd();
	if (g_data.is_dbl_and)
		check_and_op(i, j);
	else if (g_data.is_dbl_pipe)
		check_or_op(i, j);
	if (!is_redir(*j))
	{
		if (g_data.ops_array[g_data.x] == 1)
			close(g_data.fd[g_data.pipes][1]);
		dup2(g_data.fdin, STDIN_FILENO);
		dup2(g_data.fdout, STDOUT_FILENO);
	}
	if (g_data.sub_exit_flag)
		exit_shell(g_data.exit_status);
}

void	handle_cmd(void)
{
	int	k;
	int	n;

	k = 1;
	g_data.cmd_flag = 1;
	if (g_data.closing_parenthese)
	{
		g_data.closing_parenthese = 0;
		return ;
	}
	if (g_data.op_cnt > 0 && (is_pipe() || g_data.pipe_child_flag))
	{
		g_data.pipe_child_flag = 1;
		g_data.wait_n++;
		g_data.c_pid = fork();
		if (g_data.c_pid != 0)
			setup_for_pipe(&n);
	}
	compare_command(&k);
	if (g_data.c_pid == 0 && g_data.pipe_child_flag)
		exit_shell(g_data.exit_status);
}
