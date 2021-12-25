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
void	execute_commands(int i)
{
	if (!(ft_strcmp(g_data.cmd[i][0], "echo")))
			execve("/bin/echo", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "pwd")))
	{
		execve("/bin/pwd", g_data.cmd[i], g_data.environ);
	}
	else if (!(ft_strcmp(g_data.cmd[i][0], "env")))
			execve("/usr/bin/env", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "cat")))
			execve("/bin/cat", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "ls")))
			execve("/bin/ls", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "grep"))) 
			execve("/usr/bin/grep", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "wc"))) 
			execve("/usr/bin/wc", g_data.cmd[i], g_data.environ);
	else if (!(ft_strcmp(g_data.cmd[i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		exit(0);
	else if (!(ft_strcmp(g_data.cmd[i][0], "unset")))
		exit(0);
	else
		printf("bash: %s: command not found\n", g_data.cmd[i][0]);
}

char	**ft_strjoin_2d(char **str, char *str2)
{
	char **res;
	int i;

	i = 0;
	res = malloc(sizeof(char *) * (ft_strlen2(str) + 2));
	while(str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = str2;
	res[i] = NULL;
	free(str);
	return (res);
}
void	pipe_read()
{
	if (g_data.ops_array[g_data.x-1] == 1)
		{
			if(g_data.ops_array[g_data.x] != 1)
			{
				if(g_data.x == g_data.op_cnt)
					dup2(g_data.fdout, STDOUT_FILENO);
				dup2(g_data.fd[g_data.pipes][0], STDIN_FILENO);
				close(g_data.fd[g_data.pipes][0]);
			}
			else
			{
				dup2(g_data.fd[g_data.pipes-1][0], STDIN_FILENO);
				close(g_data.fd[g_data.pipes-1][0]);
			}
		}
}

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
	else if(ft_strcmp(type, "write2") == 0)
	{
		g_data.pipes++;
		pipe(g_data.fd[g_data.pipes]);
		if(!g_data.output_flag)
			dup2(g_data.fd[g_data.pipes][1], STDOUT_FILENO);
		g_data.x = *j;
		(*j)++;
		g_data.pipe_flag = 0;
	}
}

void	handle_redirection(int op, int j)
{
	int fdrd;

	if(op == 2)
	{
		fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		dup2(fdrd, STDOUT_FILENO);
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if(op == 5)
	{
		fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		dup2(fdrd, STDOUT_FILENO);
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if(op == 3)
	{
		fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT , S_IRWXU);
		dup2(fdrd, STDIN_FILENO);
		close(fdrd);
	}
}

void	check_op(int *i, int *j)
{
	int n;
	if (g_data.ops_array[*j] == 1) // 1 is pipe, so we must redirect stdout to the write side of the pipe.
		pipe_write("write", i, j);
	else if(g_data.ops_array[*j] == 2 || g_data.ops_array[*j] == 3 || g_data.ops_array[*j] == 5) // 3 is redirect input <
	{
		while(g_data.ops_array[*j] != 1 && *j < g_data.op_cnt)
		{
			n = 1;
			if(g_data.ops_array[*j] == 2)
				handle_redirection(2, *j);
			else if(g_data.ops_array[*j] == 5)
				handle_redirection(5, *j);
			else if(g_data.ops_array[*j] == 3)
				handle_redirection(3, *j);
			while(g_data.cmd[*j + 1][n])
			{
				g_data.cmd[g_data.y] = ft_strjoin_2d(g_data.cmd[g_data.y], g_data.cmd[*j + 1][n]);
				n++;
				perror("LOLAM HERE\n");
			}
			(*j)++;
		}
		*i = *j + 1;
		if (g_data.ops_array[*j] == 1)
			g_data.pipe_flag = 1;
	}
	else
		(*i)++;
}

void	handle_cmd()
{
	int k;

	k = 1;
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		while(g_data.cmd[g_data.y][k])
				ft_export(ft_strdup(g_data.cmd[g_data.y][k++]));
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "unset")))
		while(g_data.cmd[g_data.y][k])
			ft_unset(ft_strdup(g_data.cmd[g_data.y][k++]));
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "cd")))
		ft_cd();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "exit")))
	{
		printf("%s", NO_COLOR);
		ft_exit(0);
	}
	else
	{
		g_data.c_pid = fork(); // create child process
		if (g_data.c_pid == 0) // only child process goes here
		{	
			if(g_data.ops_array[g_data.x] == 1)
				close(g_data.fd[g_data.pipes][1]);
			execute_commands(g_data.y); // check for commands and execute them
		}
	}
}

void	check_cmd(void)
{
	int		i;
	int		j;

	i = 0; 
	j = 0;
	if (!*g_data.cmdline)
		return ;
	printf("|%s| \n", g_data.cmd[1][1]);
	// | = 1	> = 2	< = 3	>> = 5	<< = 6
	write(1, BYELLOW, 8);
	while(g_data.cmd[i])
	{		
		g_data.y = i;
		g_data.x = j;
		g_data.output_flag = 0;
		check_op(&i, &j);
		if(g_data.y != 0)
			pipe_read();
		if(g_data.pipe_flag == 1)
			pipe_write("write2", &i, &j);
		handle_cmd();
		if(g_data.ops_array[g_data.x] == 1)
			close(g_data.fd[g_data.pipes][1]);
		wait(0);
	}
	dup2(g_data.fdin, STDIN_FILENO);
	dup2(g_data.fdout, STDOUT_FILENO);
}