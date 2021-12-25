/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:15:01 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/25 05:16:18 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: add errors and make it for any n of commands
 */
void	ft_cd(int i)
{
	// printf("%s\n", g_data.cmd[i][1]);
	chdir(g_data.cmd[i][1]);
	// execve("/bin/pwd", NULL, NULL);
}

void	ft_echo(int i)
{
	int	n_flag;
	int	j;

	n_flag = 0;
	if (!(ft_strcmp(g_data.cmd[i][1], "-n")))
		n_flag = 1;
	j = 0;
	while (g_data.cmd[i][j])
	{
		ft_putstr_fd(g_data.cmd[i][j], 1);
		ft_putchar_fd(' ', 1);
		j++;
	}
	ft_putchar_fd('\b', 1);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

void	ft_pwd(int i)
{
	char	buffer[1000];
	char	*ret;

	if (g_data.cmd[i][1])
	{
		perror("pwd: ");
		printf("too many arguments\n");
		g_data.exit_status = 1;
	}
	ret = getcwd(buffer, sizeof(buffer));
	if (ret)
		printf("%s\n", buffer);
	else
	{
		perror("pwd: ");
		printf("%s\n", strerror(errno));
	}
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_data.environ[i])
	{
		printf("%s\n", g_data.environ[i]);
		i++;
	}
}
