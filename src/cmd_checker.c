/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/04 03:11:14 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(char *cmd)
{
	char	**av;
	char	**ev = environ;
	pid_t	pid;

	if (!*cmd)
		return ;
	av = ft_split(cmd, ' ');
	write(1, BYELLOW, 8);
	if (!(ft_strcmp(av[0], "echo")))
	{
		pid = fork();
		wait(NULL);
		if(pid == 0)
		{
			printf("%s\n", cmd);
			execve("/bin/echo", av, ev);
			exit(0);
		}
	}
	else if (!(ft_strcmp(av[0], "pwd")))
	{
		pid = fork();
		wait(NULL);
		if(pid == 0)
			execve("/bin/pwd", av, ev);
	}
	else if (!(ft_strcmp(av[0], "env")))
	{
		pid = fork();
		wait(NULL);
		if(pid == 0)
			execve("/usr/bin/env", av, ev);
	}
}