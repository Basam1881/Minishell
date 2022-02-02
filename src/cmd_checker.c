/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/02 10:03:10 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_commands(int i)
{
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "echo")))
		ft_echo();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "pwd")))
		ft_pwd();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "env")))
		ft_env();
	else
	{
		if (execve(g_data.cmd_path, g_data.cmd[i], g_data.environ) == -1)
		{
			if (g_data.is_path_flag)
			{
				if (errno == 2)
					print_error(2, i);
			}
			else
				print_error(3, i);
			exit_shell (127);
		}
	}
	exit_shell(0);
}

void	handle_other_commands(void)
{
	if (g_data.cmd_flag && !g_data.pipe_child_flag)
		g_data.c_pid = fork();
	if (g_data.c_pid != 0 && !g_data.pipe_child_flag)
		save_exit_status();
	if (g_data.c_pid == 0)
	{
		if (g_data.ops_array[g_data.x] == 1)
			close(g_data.fd[g_data.pipes][1]);
		execute_commands(g_data.y);
	}
}

void	compare_command(int	*k)
{
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "export")) && g_data.cmd_flag)
	{
		if (g_data.cmd[g_data.y][*k])
		{	
			while (g_data.cmd[g_data.y][*k])
				ft_export(ft_strdup(g_data.cmd[g_data.y][(*k)++]));
		}
		else
			empty_export();
	}
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "unset")) && g_data.cmd_flag)
		while (g_data.cmd[g_data.y][*k])
			ft_unset(ft_strdup(g_data.cmd[g_data.y][(*k)++]));
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "cd")) && g_data.cmd_flag)
		ft_cd();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "exit")) && g_data.cmd_flag)
		ft_exit();
	else
	{
		handle_other_commands();
	}
}

/*
	this is the last step in the while loop, this function will check the 
	command and execute it after all the redirections, piping are done privously
*/

void	check_cmd(void)
{
	int		i;
	int		j;
	int		error_flag;

	i = 0;
	j = 0;
	g_data.fd = malloc(sizeof(int *) * (g_data.op_cnt + 5));
	if (!g_data.cmd)
		return ;
	write(1, BYELLOW, 8);
	while (g_data.cmd[i])
	{
		if (setup_for_command(&i, &j, &error_flag))
			break ;
		if (!g_data.cmd[g_data.x][0])
		{
			if (!g_data.x)
				break ;
			else
				if (g_data.ops_array[g_data.x - 1] != 9)
					break ;
		}
		setup_operators(&i, &j, error_flag);
	}
	write(1, NO_COLOR, 4);
}
