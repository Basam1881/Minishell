/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/17 04:00:17 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	always check the paths of executebles, i had to change some of them when i used my laptop.
*/
void	execute_commands(int *i)
{
	if (!(ft_strcmp(g_data.cmd[*i][0], "echo")))
			execve("/bin/echo", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "pwd")))
	{
		execve("/bin/pwd", g_data.cmd[*i], g_data.environ);
	}
	else if (!(ft_strcmp(g_data.cmd[*i][0], "env")))
			execve("/usr/bin/env", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "cat")))
			execve("/bin/cat", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "ls")))
			execve("/bin/ls", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "grep"))) 
			execve("/usr/bin/grep", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "wc"))) 
			execve("/usr/bin/wc", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		exit(0);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "unset")))
		exit(0);
	else
		printf("bash: %s: command not found\n", g_data.cmd[*i][0]);
}

void	check_cmd(void)
{
	int		i;
	int		j;
	int 	y;
	int 	k;
	int		fd[g_data.op_cnt][2];
	int		fdrd;
	int 	x;
	i = 0; 
	j = 0;
	if (!*g_data.cmdline)
		return ;
	int fdout = dup(STDOUT_FILENO);
	int fdin = dup(STDIN_FILENO);

	/*
	| = 1
	> = 2
	< = 3
	>> = 5
	<< = 6
	*/
	write(1, BYELLOW, 8);
	while(g_data.cmd[i])
	{		
		//cmd_filter(i);
		y = i;
		x = j;
		g_data.output_flag = 0;
			if (g_data.ops_array[j] == 1) // 1 is pipe, so we must redirect stdout to the write side of the pipe.
			{
				g_data.pipes++;
				pipe(fd[g_data.pipes]);
				dup2(fd[g_data.pipes][1], STDOUT_FILENO);
				i++;
				j++;
			}
			else if(g_data.ops_array[j] == 2 || g_data.ops_array[j] == 3 || g_data.ops_array[j] == 5) // 3 is redirect input <
			{
				while(g_data.ops_array[j] != 1 && j < g_data.op_cnt)
				{

					if(g_data.ops_array[j] == 2)
					{
						fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
						dup2(fdrd, STDOUT_FILENO);
						close(fdrd);
						g_data.output_flag = 1;
					}
					if(g_data.ops_array[j] == 5)
					{
						fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
						dup2(fdrd, STDOUT_FILENO);
						close(fdrd);
						g_data.output_flag = 1;
					}
					if(g_data.ops_array[j] == 3)
					{
						fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
						dup2(fdrd, STDIN_FILENO);
						close(fdrd);
					}
					j++;
				}
				if(j == g_data.op_cnt)
					i = j + 1;
				else
				{
					g_data.pipe_flag = 1;
					i = j + 1;
				}
			}
			else
			{
				i++;
			}
			if(y != 0)
			{
				if (g_data.ops_array[x-1] == 1)
				{
				if(g_data.ops_array[x] != 1)
				{
					if(x == g_data.op_cnt)
						dup2(fdout, STDOUT_FILENO);
					dup2(fd[g_data.pipes][0], STDIN_FILENO);
					close(fd[g_data.pipes][0]);
				}
				else
				{
					dup2(fd[g_data.pipes-1][0], STDIN_FILENO);
					close(fd[g_data.pipes-1][0]);
				}
				}
			}
		if(g_data.pipe_flag == 1)
		{
			g_data.pipes++;
			pipe(fd[g_data.pipes]);
			if(!g_data.output_flag)
				dup2(fd[g_data.pipes][1], STDOUT_FILENO);
			x = j;
			j++;
			g_data.pipe_flag = 0;
		}
		if (!(ft_strcmp(g_data.cmd[y][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		{
			k = 1;
			while(g_data.cmd[y][k])
				ft_export(ft_strdup(g_data.cmd[y][k++]));
		}
		else if (!(ft_strcmp(g_data.cmd[y][0], "unset")))
		{
			k = 1;
			while(g_data.cmd[y][k])
				ft_unset(ft_strdup(g_data.cmd[y][k++]));
		}
		else if (!(ft_strcmp(g_data.cmd[y][0], "cd")))
			ft_cd();
		else if (!(ft_strcmp(g_data.cmd[y][0], "exit")))
		{
			printf("%s", NO_COLOR);
			ft_exit(0);
		}
		else
		{
			g_data.c_pid = fork(); // create child process
			if (g_data.c_pid == 0) // only child process goes here
			{	
				usleep(2000);
				if(g_data.ops_array[x] == 1)
					close(fd[g_data.pipes][1]);
				execute_commands(&y); // check for commands and execute them
			}
		}
		if(g_data.ops_array[x] == 1)
			close(fd[g_data.pipes][1]);
		wait(0);
	}
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}