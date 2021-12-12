/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/11 15:27:37 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	always check the paths of executebles, i had to change some of them when i used my laptop.
*/
void	execute_commands(t_data *data, int *i)
{
	if (!(ft_strcmp(data->cmd[*i][0], "echo")))
			execve("/bin/echo", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "pwd")))
			execve("/bin/pwd", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "cd")))
			execve("/usr/bin/cd", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "env")))
			execve("/usr/bin/env", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "cat")))
			execve("/bin/cat", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "ls")))
			execve("/bin/ls", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "grep"))) 
			execve("/usr/bin/grep", data->cmd[*i], environ);
	else if (!(ft_strcmp(data->cmd[*i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
	{
		ft_export(data->cmd[*i][1]);
		exit(0);
	}
	else if (!(ft_strcmp(data->cmd[*i][0], "unset")))
	{
		ft_unset(data->cmd[*i][1]);
		exit(0);
	}
	else if (!(ft_strcmp(data->cmd[*i][0], "exit")))
	{
		printf("%s", NO_COLOR);
		ft_exit(data, 0);
	}
	else
		printf("bash: %s: command not found\n", data->cmd[*i][0]);
}

void	check_cmd(t_data *data)
{
	pid_t	pid;
	int		i;
	int		j;
	int		fd[2];
	int		fdrd;
	i = 0; 
	j = 2; // This was suppoed to be the number of operators, but for some reason op_cnt is 1 always so i put it manual for now;
	if (!*data->cmdline)
		return ;
	write(1, BYELLOW, 8);
	pipe(fd); // create the pipe fd[0] =  read side of the pipe , fd[1] = write side of the pipe
	while(j--)
	{
		if(data->ops_array[i] == 2 || data->ops_array[i] == 3)
			j--;
		pid = fork(); // create child process
		if (pid == 0) // only child process goes here
		{
			if (data->ops_array[i] == 1) // 1 is pipe, so we must redirect stdout to the write side of the pipe.
				dup2(fd[1], STDOUT_FILENO);
			else if(data->ops_array[i] == 2) // 2 is redirect, so we must redirect stdout to the file given on input.
			{
				fdrd = open(data->cmd[i+1][0], O_RDWR | O_CREAT, S_IRWXU);
				dup2(fdrd, STDOUT_FILENO);
			}
			else if(data->ops_array[i] == 3) // 3 is redirect append, so we must redirect stdout to the file given on input.
			{
				fdrd = open(data->cmd[i+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
				dup2(fdrd, STDOUT_FILENO);
			}
			else // if there is no pipe or redirect reset everything to nomral. still not sure but i think we can remove this part.
			{
				dup2(1, STDOUT_FILENO);
				dup2(0, STDIN_FILENO);
			}
			if (data->ops_array[i-1] == 1 && i != 0)
				dup2(fd[0], STDIN_FILENO);

			close(fd[1]);
			close(fd[0]);
			execute_commands(data, &i); // check for commands and execute them
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	while(i--)
		wait(0);
}
