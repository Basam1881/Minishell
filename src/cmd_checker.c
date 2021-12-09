/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/09 19:32:18 by mal-guna         ###   ########.fr       */
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
	int optr[3];
	optr[0] = 1; // 1 for pipe
	optr[1] = 2; // 1 for redirction
	int i = 1;
	
	while(i--)
	{
		execute_commands(av);
	}
}

void	execute_commands(char **av)
{
	pid_t	pid;
	int		fd[2];

/* 	printf("|%s|\n", av[0]);
	printf("|%s|\n", av[1]);
	printf("|%s|\n", av[2]);
	printf("|%s|\n", av[3]);
 */
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (0) /* here we will check if there is an operator so we change the output fd */
			dup2(fd[1], STDOUT_FILENO);
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
		close(fd[0]);
		close(fd[1]);
	}
	
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}