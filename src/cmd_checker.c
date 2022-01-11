/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/11 16:45:48 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: move the exit function to the parent part not for the child
 * TODO: remove the export and unset function from the child part as well
 * TODO: if the command is not found then exit the child process with 127
 * TODO: add clear command to the execve part
 * TODO: protect check_cmd by checking cmd not cmdline
 * ! remember to dup back the file describtors to not cause errors later on
 * ? Do we need to make sure that child processors are freed before passing them to execve!!
 **/
/*
	This funciton will simply execute the commands using execve 
*/
void	execute_commands(int i)
{
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "echo")))
		ft_echo();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "env")))
		ft_env();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "pwd")))
		ft_pwd();
	else if (execve(g_data.cmd_path, g_data.cmd[i], g_data.environ) == -1)
	{
		ft_putstr_fd("BNM bash: ", 2);
		ft_putstr_fd(g_data.cmd[i][0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putchar_fd('\n', 2);
		exit_shell (127);
	}
	exit_shell(0);
}

/* 
	This function will be called if there are more arguments other than file name ( only with redirections )
*/
void	ft_strjoin_2d(char *str2)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (ft_strlen2(g_data.cmd[g_data.y]) + 2));
	while (g_data.cmd[g_data.y][i])
	{
		res[i] = ft_strdup(g_data.cmd[g_data.y][i]);
		i++;
	}
	res[i++] = ft_strdup(str2);
	res[i] = NULL;
	i = 0;
	while (g_data.cmd[g_data.y][i])
		free(g_data.cmd[g_data.y][i++]);
	free(g_data.cmd[g_data.y][i]);
	free(g_data.cmd[g_data.y]);
	g_data.cmd[g_data.y] = res;
}

/*
	this function will redirect the input source to the read side of the pipe (Only if needed !)
*/
void	pipe_read(void)
{
	if (g_data.ops_array[g_data.x - 1] == 1)
	{
		if (g_data.ops_array[g_data.x] != 1)
		{
			if (g_data.x == g_data.op_cnt)
				dup2(g_data.fdout, STDOUT_FILENO);
			if (!g_data.input_flag)
				dup2(g_data.fd[g_data.pipes][0], STDIN_FILENO);
			close(g_data.fd[g_data.pipes][0]);
		}
		else
		{
			if (!g_data.input_flag)
				dup2(g_data.fd[g_data.pipes - 1][0], STDIN_FILENO);
			close(g_data.fd[g_data.pipes - 1][0]);
		}
	}
}

/* 
	this function will redirect the output source to the write side of the pipe (Only if needed !)
*/
void	pipe_write(char *type, int *i, int *j)
{
	if (ft_strcmp(type, "write") == 0)
	{
		g_data.pipes++;
		pipe(g_data.fd[g_data.pipes]);
		dup2(g_data.fd[g_data.pipes][1], STDOUT_FILENO);
		(*j)++;
		(*i)++;
		g_data.is_pipe = 1;
	}
	else if (ft_strcmp(type, "write2") == 0)
	{
		g_data.pipes++;
		pipe(g_data.fd[g_data.pipes]);
		if (!g_data.output_flag)
			dup2(g_data.fd[g_data.pipes][1], STDOUT_FILENO);
		g_data.x = *j;
		(*j)++;
	}
}

/*
	this function will handle the rederctions and link the givein files to the stdout or stdin, also it will use ft_strjoin_2d to append any extry args to g_data.cmd
*/
int	handle_redirection(int op, int j)
{
	int		fdrd;
	int		inputfd[2];
	char	*temp;

	if (op == 2)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fdrd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		if (dup2(fdrd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if (op == 5)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fdrd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		if (dup2(fdrd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if (op == 3)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR, S_IRWXU);
		if (fdrd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		if (dup2(fdrd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		close(fdrd);
		g_data.input_flag = 1;
	}
	else if (op == 6)
	{
		pipe(inputfd);
		//dup2(g_data.fdin, STDIN_FILENO);
		while (1)
		{
			temp = get_next_line(g_data.fdin);
			if ((ft_strncmp(temp, g_data.cmd[j + 1][0], ft_strlen(temp) - 1) || !ft_strcmp(temp, "\n")) == 0 && temp)
				break ;
			write(inputfd[1], temp, ft_strlen(temp));
			free(temp);
			temp = NULL;
		}
		//dup2(g_data.fdin, STDIN_FILENO);
		if (dup2(inputfd[0], STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			return (1);
		}
		close(inputfd[0]);
		close(inputfd[1]);
		g_data.input_flag = 1;
	}
	return (0);
}

int	is_redir(int j)
{
	if (g_data.ops_array[j] == 2 || g_data.ops_array[j] == 3
		|| g_data.ops_array[j] == 5 || g_data.ops_array[j] == 6)
		return (1);
	return (0);
}

/*
	this function will check for any pipes or redirections and call the crosponding fucntions to handle them.
*/
int	check_op(int *i, int *j)
{
	int	n;

	if (g_data.ops_array[*j] == 1)
		pipe_write("write", i, j);
	else if (is_redir(*j))
	{
		while (is_redir(*j) && *j < g_data.op_cnt)
		{
			n = 1;
			if (handle_redirection(g_data.ops_array[*j], *j))
			{
				return (1);
			}
			while (g_data.cmd[*j + 1][n])
			{
				ft_strjoin_2d(g_data.cmd[*j + 1][n]);
				n++;
			}
			(*j)++;
		}
		*i = *j + 1;
		if (g_data.ops_array[*j] == 1)
			g_data.pipe_flag = 1;
		else if (g_data.ops_array[*j] == 4)
		{
			// g_data.pipe_flag = 1;
			g_data.is_dbl_pipe = 1;
		}
		else if (g_data.ops_array[*j] == 7)
		{
			// g_data.pipe_flag = 1;
			g_data.is_dbl_and = 1;
		}
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
	else
		(*i)++;
	return (0);
}

/*
	this is the last step in the while loop, this function will check the command and execute it after all the redirections, piping are done privously
*/
void	handle_cmd(void)
{
	int	k;

	k = 1;
	if (!(ft_strcmp(g_data.cmd[g_data.y][0], "export")))
		while (g_data.cmd[g_data.y][k])
			ft_export(ft_strdup(g_data.cmd[g_data.y][k++]));
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "unset")))
		while (g_data.cmd[g_data.y][k])
			ft_unset(ft_strdup(g_data.cmd[g_data.y][k++]));
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "cd")))
		ft_cd();
	else if (!(ft_strcmp(g_data.cmd[g_data.y][0], "exit")))
		ft_exit();
	else
	{
		g_data.c_pid = fork();
		save_exit_status();
		if (g_data.c_pid == 0)
		{
			if (g_data.ops_array[g_data.x] == 1)
				close(g_data.fd[g_data.pipes][1]);
			execute_commands(g_data.y);// check for commands and execute them
		}
	}
}

void	dbl_ops_handler(void)
{
	return ;
}

void	check_cmd(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!g_data.cmd)
		return ;
	// | = 1	> = 2	< = 3	>> = 5	<< = 6
	write(1, BYELLOW, 8);
	while (g_data.cmd[i])
	{
		g_data.y = i;
		g_data.x = j;
		g_data.output_flag = 0;
		g_data.input_flag = 0;
		cmd_filter(i);
		// printf("|%s|\n", g_data.cmd_path);
		// g_data.cmd[g_data.y][0] = g_data.cmd_path;
		// printf("~%d~ ~%s~\n", i, g_data.cmd[g_data.y][0]);
		if (check_op(&i, &j))
			break ;
		if (g_data.y != 0)
		{
			if ((g_data.is_dbl_pipe || g_data.is_dbl_and) && !g_data.pipe_flag)
			{
				dup2(g_data.fdout, STDOUT_FILENO);
				// g_data.is_dbl_and = 0;
				// g_data.is_dbl_pipe = 0;
			}
			else
				pipe_read();
		}
		if (g_data.pipe_flag == 1)
		{
			// printf("SHIT\n");
			if (g_data.is_dbl_pipe || g_data.is_dbl_and)
			{
				// if (g_data.ops_array[j] != 4 && g_data.ops_array[j] != 7)
				// g_data.x = j;
				j++;
				// else
				// 	i++;
			}
			else
				pipe_write("write2", &i, &j);
			g_data.pipe_flag = 0;
		}
		handle_cmd();
		if (g_data.is_dbl_and)
		{
			dup2(g_data.fdout, STDOUT_FILENO);
			if (g_data.exit_status)
				break ;
			g_data.is_dbl_and = 0;
		}
		else if (g_data.is_dbl_pipe)
		{
			dup2(g_data.fdout, STDOUT_FILENO);
			if (!g_data.exit_status)
				break ;
			g_data.is_dbl_pipe = 0;
		}
		// printf("j: %d\tx: %d\t i: %d\ty: %d\n", j, g_data.x, i, g_data.y);
		if (!is_redir(j))
			close(g_data.fd[g_data.pipes][1]);
		wait(NULL);
	}
	dup2(g_data.fdin, STDIN_FILENO);
	dup2(g_data.fdout, STDOUT_FILENO);
}
