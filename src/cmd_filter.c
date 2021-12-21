/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 00:36:24 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/21 05:17:54 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * save_exit_status() function is used to let the parent process wait 
 * 		for the child process, then after the child process die
 * 		the parent process check the exit status for the child process only.
 * 		(the exit status for the other commands that doesn't need child process
 * 		will be checked insided the functions' themselves)
 * TODO: check the exit status for export, unset and cd for all conditions and save their exit status in g_data.exit_status
 */
void	save_exit_status(void)
{
	int		status;
	wait(&status);
	if (g_data.c_pid != 0)
	{
		// if (g_data.c_exit_flag)
		// {
			// printf ("exit\n");
			g_data.exit_status = WEXITSTATUS(status);
			g_data.c_exit_flag = 0;
		// }
		// printf ("exit child with %d\n", g_data.exit_status);
	}
}

/**
 * This function should be called from cmd_checker function
 * It should be called for each command
 * It will not return anything but it will change the value of g_data.cmd_path
 * g_data.cmd_path is a variable that contain the path joined with the command.
 * 		if there the first arg in the cmd is not a path and it's not included
 * 		in $PATH g_data.cmd_path will be NULL
 * * ft_strjoin has been modified to not free the second string (g_data.cmd[i][0])
 **/
void	cmd_filter(int i)
{
	char	**path;
	int		j;
	char	*en;

	path = NULL;
	if (g_data.cmd[i][0][0] == '/' || g_data.cmd[i][0][0] == '.')
		g_data.cmd_path = g_data.cmd[i][0];
	else
	{
		en = getenv("PATH");
		path = ft_split(en, ':');
		j = 0;
		while (path[j])
		{
			path[j] = ft_strjoin(path[j], "/");
			path[j] = ft_strjoin(path[j], g_data.cmd[i][0]);
			if (!access(path[j], F_OK))
			{
				g_data.cmd_path = path[j];
				j = 0;
				while (path[j])
					free(path[j++]);
				free(path);
				return ;
			}
			j++;
		}
		g_data.cmd_path = NULL;
	}
}
