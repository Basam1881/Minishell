/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/25 05:03:45 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * TODO: add the error part to execve for m_branch
 * TODO: move the exit function to the parent part not for the child
 * TODO: remove the export and unset function from the child part as well
 * TODO: if the command is not found then exit the child process with 127
 * TODO: add clear command to the execve part
 * ? Do we need to make sure that child processors are freed before passing them to execve!!
 **/
void	execute_commands(int *i)
{
	if (!(ft_strcmp(g_data.cmd[*i][0], "echo")))
	{
		if (execve("/bin/echo", g_data.cmd[*i], g_data.environ) == -1)
			printf("zsh: %s\nexit: %d\n", strerror(errno), errno);
	}
	else if (!(ft_strcmp(g_data.cmd[*i][0], "pwd")))
	{
		// printf("g_data.cmd_path: %s\n", g_data.cmd_path);
		if (execve(g_data.cmd_path, g_data.cmd[*i], g_data.environ) == -1)
			printf("zsh: %s\n", strerror(errno));
	}
	else if (!(ft_strcmp(g_data.cmd[*i][0], "cd")))
	{
		ft_cd(*i);
	}
	else if (!(ft_strcmp(g_data.cmd[*i][0], "env")))
		execve("/usr/bin/env", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "cat")))
		execve("/bin/cat", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "ls")))
		execve("/bin/ls", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "clear")))
		execve("/usr/bin/clear", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "grep")))
		execve("/usr/bin/grep", g_data.cmd[*i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		ft_exit(g_data.exit_status);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "unset")))
		ft_exit(g_data.exit_status);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "exit")))
		ft_exit(g_data.exit_status);
	else
		printf("bash: %s: command not found\n", g_data.cmd[*i][0]);
	ft_exit(127);
}

void	check_cmd(void)
{
	int		i;
	int		j;
	int		fd[2];
	int		fdrd;

	i = 0;
	j = g_data.op_cnt + 1; // This was suppoed to be the number of operators, but for some reason op_cnt is 1 always so i put it manual for now;
	if (!g_data.cmd)
		return ;
	write(1, BYELLOW , 8);
	pipe(fd); // create the pipe fd[0] =  read side of the pipe , fd[1] = write side of the pipe
	while(j--)
	{
		cmd_filter(i);
		if(g_data.ops_array[i] == 2 || g_data.ops_array[i] == 5)
			j--;
		g_data.c_pid = fork(); // create child process
		save_exit_status();
		if (g_data.c_pid == 0) // only child process goes here
		{
			if (g_data.ops_array[i] == 1) // 1 is pipe, so we must redirect stdout to the write side of the pipe.
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			else if(g_data.ops_array[i] == 2) // 2 is redirect, so we must redirect stdout to the file given on input.
			{
				fdrd = open(g_data.cmd[i+1][0], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
				dup2(fdrd, STDOUT_FILENO);
			}
			else if(g_data.ops_array[i] == 5) // 3 is redirect append, so we must redirect stdout to the file given on input.
			{
				fdrd = open(g_data.cmd[i+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
				dup2(fdrd, STDOUT_FILENO);
			}
			else // if there is no pipe or redirect reset everything to nomral. still not sure but i think we can remove this part.
			{
				dup2(1, STDOUT_FILENO);
				dup2(0, STDIN_FILENO);
				j--;
			}
			if (g_data.ops_array[i-1] == 1 && i != 0)
				dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execute_commands(&i); // check for commands and execute them
		}
		else if (!(ft_strcmp(g_data.cmd[i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		{
			ft_export(ft_strdup(g_data.cmd[i][1]));
		}
		else if (!(ft_strcmp(g_data.cmd[i][0], "unset")))
		{
			ft_unset(ft_strdup(g_data.cmd[i][1]));
		}
		else if (!(ft_strcmp(g_data.cmd[i][0], "exit")))
		{
			// printf("cmd\n");
			cmd_exit(i);
		}
		i++;
		// printf("HEREPPP\n");
	}
	close(fd[0]);
	close(fd[1]);
	while (i--)
		wait(NULL);
}
