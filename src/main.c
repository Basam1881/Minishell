/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/28 09:45:06 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **ev)
{
	struct sigaction	sig_sig;

	(void) ac;
	(void) av;
	g_data.environ = ev;
	sig_sig.sa_flags = 0;
	sig_sig.sa_mask = 0;
	sig_sig.sa_sigaction = &sig_handler;
	sigaction(SIGINT, &sig_sig, NULL);
	initialize();
	printf("\033[?1049h\033[H");
	while (1)
	{
		g_data.c_pid = 1;
		g_data.cmdline = readline(MAC_PROMPT);
		// g_data.cmdline = "echo hi $_ '' wow > beso || grep we wa << woo >> yes      | hi && trick & yeah";
		if (!g_data.cmdline)
			ft_exit(0);
		if (g_data.cmdline && *g_data.cmdline)
			add_history(g_data.cmdline);
		ultimate_3d_split();
		check_cmd();
		free_all();
	}
	return (0);
}
