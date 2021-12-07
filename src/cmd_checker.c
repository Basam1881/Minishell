/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/07 10:59:47 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(char *cmd)
{
	char	**av;

	if (!*cmd)
		return ;
	av = ft_split(cmd, ' ');
	write(1, BYELLOW, 8);
	while(1)
	{
		execute_commands(av);
	}
}

void	execute_commands(char **av)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		if (!(ft_strcmp(av[0], "echo")))
			execve("/bin/echo", av, environ);
		else if (!(ft_strcmp(av[0], "pwd")))
			execve("/bin/pwd", av, environ);
		else if (!(ft_strcmp(av[0], "env")))
			execve("/usr/bin/env", av, environ);
		else if (!(ft_strcmp(av[0], "export")))
			ft_export(av[1]);
		else if (!(ft_strcmp(av[0], "unset")))
			ft_unset(av[1]);
		else
			printf("%s: command not found\n", av[0]);
	}
	waitpid(pid, NULL, 0);
}