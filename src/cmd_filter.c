/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 00:36:24 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/18 04:13:53 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This finction should be called from cmd_checker function
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

	path = NULL;
	if(g_data.cmd_path)
	{
		free(g_data.cmd_path);
		g_data.cmd_path = NULL;
	}
	if (g_data.cmd[i][0][0] == '/' || g_data.cmd[i][0][0] == '.')
		g_data.cmd_path = g_data.cmd[i][0];
	else
	{
		path = ft_split(getenv("PATH"), ':');
		j = 0;
		while (path[j])
		{
			path[j] = ft_strjoin(path[j], "/");
			path[j] = ft_strjoin(path[j], g_data.cmd[i][0]);
			if (!access(path[j], F_OK))
			{
				g_data.cmd_path = ft_strdup(path[j]);
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
