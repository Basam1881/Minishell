/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:21:42 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 10:50:25 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_input(int j)
{
	int		inputfd[2];
	char	*temp;

	pipe(inputfd);
	while (1)
	{
		temp = get_next_line(g_data.fdin);
		if (!temp)
			break ;
		if (ft_strlen(g_data.cmd[j + 1][0]) == (ft_strlen(temp) - 1)
			&& !(ft_strncmp(temp, g_data.cmd[j + 1][0], ft_strlen(temp) - 1)))
		{
			if (temp)
				free(temp);
			break ;
		}
		write(inputfd[1], temp, ft_strlen(temp));
		free(temp);
	}
	if (dup2(inputfd[0], STDIN_FILENO) == -1)
		return (1);
	close(inputfd[0]);
	close(inputfd[1]);
	g_data.input_flag = 1;
	return (0);
}

int	redirect_output(int j, int type)
{
	int	fdrd;

	if (type == 1)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fdrd == -1)
			return (1);
		if (dup2(fdrd, STDOUT_FILENO) == -1)
			return (1);
		close(fdrd);
		g_data.output_flag = 1;
		return (0);
	}
	if (type == 2)
	{
		fdrd = open(g_data.cmd[j + 1][0], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fdrd == -1)
			return (1);
		if (dup2(fdrd, STDOUT_FILENO) == -1)
			return (1);
		close(fdrd);
		g_data.output_flag = 1;
	}
	return (0);
}

int	redirect_input(int j)
{
	int	fdrd;

	fdrd = open(g_data.cmd[j + 1][0], O_RDWR, S_IRWXU);
	if (fdrd == -1)
		return (1);
	if (dup2(fdrd, STDIN_FILENO) == -1)
		return (1);
	close(fdrd);
	g_data.input_flag = 1;
	return (0);
}

/**
 * this function will handle the rederctions and link the givein files
 * to the stdout or stdin, also it will use ft_strjoin_2d to append any
 * extry args to g_data.cmd
 */
int	handle_redirection(int op, int j)
{
	if (op == 2)
	{
		if (redirect_output(j, 1))
			return (1);
	}
	else if (op == 5)
	{
		if (redirect_output(j, 2))
			return (1);
	}
	else if (op == 3)
	{
		if (redirect_input(j))
			return (1);
	}
	else if (op == 6)
	{
		if (double_input(j))
			return (1);
	}
	return (0);
}
