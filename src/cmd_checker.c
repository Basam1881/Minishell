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
	else if (!(ft_strcmp(g_data.cmd[*i][0], "export"))) // export and unset are acting weried when i used the 3d array, i will fix them tommrow.
		exit(0);
	else if (!(ft_strcmp(g_data.cmd[*i][0], "unset")))
		exit(0);
	else
		printf("bash: %s: command not found\n", g_data.cmd[*i][0]);
}

	int copy_fd(int fd1)
	{
		return (dup(fd1));
	}

void	check_cmd(void)
{
	int		i;
	int		j;
	int 	y;
	int 	k;
	int		fd[2];
	int     fd2[2];
	int		fdrd;
	fd[0]= -1;
	fd[1]= -1;
	fd2[0]= -1;
	fd2[1]= -1;
	g_data.file_input = 0;
	i = 0; 
	j = 0;
	//j = g_data.op_cnt + 1; // This was suppoed to be the number of operators, but for some reason op_cnt is 1 always so i put it manual for now;
	if (!*g_data.cmdline)
		return ;
	int fdout = dup(STDOUT_FILENO);
	int fdin = dup(STDIN_FILENO);

	//printf("> = %d\n", g_data.ops_array[0]);
	//printf("< = %d\n", g_data.ops_array[1]);
	//printf(">> = %d\n", g_data.ops_array[2]);
	//printf("<< = %d\n", g_data.ops_array[3]);

	/*
	| = 1
	> = 2
	< = 3
	>> = 5
	<< = 6
	*/
	write(1, BYELLOW, 8);
	pipe(fd);
	//char *test = malloc(sizeof(char *) * 1000);

	while(g_data.cmd[i])
	{		
		y = i;
		pipe(fd2);
		if(i != 0)
		{
			int n = 1;
			int w = 0;
			char test[200];
			//dup2(fdout, STDOUT_FILENO);

			while(n==1)
			{
				n = read(fd[0], test, 1);
				w = w + n;
				printf("%s\n", test);
			}
			printf("kdjflakjd\n");
			// char *test1 = malloc(sizeof(char) * n + 1);
			// test1[n]='\0';
			// while(n--)
			// {
			// 	test1[n] = test[n];
			// }
			w = write(fd2[1], test, w);

			// if(y == 1)	
			// {	
			// 	dup2(fdout, STDOUT_FILENO);
			// 	printf("|%s|\n", test);
			// }
		}
			if (g_data.ops_array[j] == 1) // 1 is pipe, so we must redirect stdout to the write side of the pipe.
			{
				dup2(fd[1], STDOUT_FILENO);
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
					}
					if(g_data.ops_array[j] == 5)
					{
						fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
						dup2(fdrd, STDOUT_FILENO);
						close(fdrd);
					}
					if(g_data.ops_array[j] == 3)
					{
						fdrd = open(g_data.cmd[j+1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
						dup2(fdrd, STDIN_FILENO);
						close(fdrd);
						g_data.file_input = 1;
					}
					j++;
				}
				if(j == g_data.op_cnt)
					i = j + 1;
				else
					i = j + 1;
			}
			else
			{
				i++;
			}

			if(y != 0)
			{
				if (g_data.ops_array[j-1] == 1)
				{

					dup2(fd2[0], STDIN_FILENO);
					if(g_data.ops_array[j] != 1)
						dup2(fdout, STDOUT_FILENO);
				}
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
				close(fd2[1]);
				close(fd2[0]);
				close(fd[0]);
				close(fd[1]);
				execute_commands(&y); // check for commands and execute them
			}
		}
		close(fd2[0]);
		close(fd2[1]);
		wait(0);
	}
	close(fd[0]);
	close(fd[1]);
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	
	// close(fd[0]);
	// close(fd[1]);
	// while(i--)
	// 	wait(0);
	
	//wait(0);
}