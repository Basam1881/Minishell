/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 01:38:25 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: don't forget to clear the history before you exit the program
 */
int	main(int ac, char **av, char **ev)
{
	int i;

	i = -1;
	(void) ac;
	(void) av;
	g_data.environ = (char **)malloc(sizeof(char **) * (ft_strlen2(ev) + 1));
	while (ev[++i])
		g_data.environ[i] = ft_strdup(ev[i]);
	g_data.environ[i] = NULL;
	init();
	reset();
	printf(CLEAR_SCREEN);
	while (1)
	{
		g_data.cmdline = readline(LINUX_PROMPT);
		// g_data.cmdline = "(cd .. && pwd)";
		if (!g_data.cmdline)
		{
			ft_putendl_fd("exit", 1);
			exit_shell(g_data.exit_status);
		}
		if (g_data.cmdline && *g_data.cmdline)
			add_history(g_data.cmdline);
		if (!ultimate_3d_split())
			check_cmd();
		free_all();
	}
}
