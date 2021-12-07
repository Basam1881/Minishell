/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/07 15:33:11 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(void)
{
	char	**av;
	pid_t	pid;

	if (!*(g_data.cmdline))
		return ;
	av = cmd_split();
	write(1, BYELLOW, 8);
	if (!(ft_strcmp(av[0], "echo")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
		{
			execve("/bin/echo", av, g_data.env);
			exit(0);
		}
	}
	else if (!(ft_strcmp(av[0], "pwd")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
			execve("/bin/pwd", av, g_data.env);
	}
	else if (!(ft_strcmp(av[0], "env")))
	{
		pid = fork();
		wait(NULL);
		if (pid == 0)
			execve("/usr/bin/env", av, g_data.env);
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
