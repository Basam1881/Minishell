/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/15 15:21:43 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: don't forget to clear the history before you exit the program
 */
int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	g_data.environ = ev;
	init();
	reset();
	printf(CLEAR_SCREEN);
	while (1)
	{
		g_data.cmdline = readline(MAC_PROMPT);
		// g_data.cmdline = "echo hi > 1 || echo wow";
		if (!g_data.cmdline)
			exit_shell(g_data.exit_status);
		if (g_data.cmdline && *g_data.cmdline)
			add_history(g_data.cmdline);
		ultimate_3d_split();
		check_cmd();
		free_all();
	}
}
