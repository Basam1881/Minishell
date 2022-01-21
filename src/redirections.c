/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:21:42 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/20 22:20:07 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The is_resdir() function checks if the current operator in g_data.ops_array
 * is redirection or not. It returns 1 if it is and 0 if it's not.
**/
int	is_redir(int j)
{
	if (g_data.ops_array[j] == 2 || g_data.ops_array[j] == 3
		|| g_data.ops_array[j] == 5 || g_data.ops_array[j] == 6)
		return (1);
	return (0);
}

/* 
	This function will be called if there are more arguments
	other than file name ( only with redirections )
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
	free(g_data.cmd[g_data.y]);
	g_data.cmd[g_data.y] = res;
}

/*
	this function will handle the rederctions and link the givein files
	to the stdout or stdin, also it will use ft_strjoin_2d to append any
	extry args to g_data.cmd
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
			return (1);
		if (dup2(fdrd, STDOUT_FILENO) == -1)
			return (1);
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if (op == 5)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fdrd == -1)
			return (1);
		if (dup2(fdrd, STDOUT_FILENO) == -1)
			return (1);
		close(fdrd);
		g_data.output_flag = 1;
	}
	else if (op == 3)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR, S_IRWXU);
		if (fdrd == -1)
			return (1);
		if (dup2(fdrd, STDIN_FILENO) == -1)
			return (1);
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
			if (ft_strlen(g_data.cmd[j + 1][0]) == (ft_strlen(temp) - 1) && !(ft_strncmp(temp, g_data.cmd[j + 1][0], ft_strlen(temp) - 1)) )
			{
				if(temp)
					free(temp);
				break ;
			}
			write(inputfd[1], temp, ft_strlen(temp));
			free(temp);
			temp = NULL;
		}
		//dup2(g_data.fdin, STDIN_FILENO);
		if (dup2(inputfd[0], STDIN_FILENO) == -1)
			return (1);
		close(inputfd[0]);
		close(inputfd[1]);
		g_data.input_flag = 1;
	}
	return (0);
}
