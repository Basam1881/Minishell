/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:02:06 by bnaji             #+#    #+#             */
/*   Updated: 2021/11/30 17:04:00 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(char *cmd)
{
	// char	*av[] = {"hello", "world", NULL};
	// char	*ev[] = {"hi", "bassam", NULL};
	// pid_t pid = fork();
	if (!(ft_strncmp(cmd, "echo ", 5)))
		printf("\033[1;33m%s\n", cmd + 5);
		// if(pid == 0)
		// 	execve("/bin/echo", av, ev);
		// if(pid == 0)
		// 	exit(0);
}
