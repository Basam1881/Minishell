/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/14 12:58:11 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(t_data *data)
{
	char	**av;
	pid_t	pid;

	if (!*data->cmdline)
		return ;
	av = data->cmd[0];
	write(1, BYELLOW, 8);
	if (!(ft_strcmp(av[0], "echo")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
		{
			execve("/bin/echo", av, environ);
			exit(0);
		}
	}
	else if (!(ft_strcmp(av[0], "pwd")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
			execve("/bin/pwd", av, environ);
	}
	else if (!(ft_strcmp(av[0], "cd")))
	{
		ft_cd(data);
	}
	else if (!(ft_strcmp(av[0], "env")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
			execve("/usr/bin/env", av, environ);
	}
	else if (!(ft_strcmp(av[0], "export")))
	{
		ft_export(av[1]);
	}
	else if (!(ft_strcmp(av[0], "unset")))
	{
		ft_unset(av[1]);
	}
	else if (!(ft_strcmp(av[0], "exit")))
	{
		printf("%s", NO_COLOR);
		ft_exit(data, 0);
	}
	else
	{
		printf("zsh: command not found: %s\n", av[0]);
	}
}
