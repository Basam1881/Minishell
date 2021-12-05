/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/05 06:47:34 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(char *cmd)
{
	char	**av;
	pid_t	pid;

	if (!*cmd)
		return ;
	av = ft_split(cmd, ' ');
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
	else
	{
		printf("%s: command not found\n", av[0]);
	}
}