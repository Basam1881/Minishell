/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/07 15:56:09 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	g_data.env = ev;
	printf("\033[?1049h\033[H");
	while (1)
	{
		printf("\033[m");
		g_data.cmdline = readline("\033[1;34m⚡⚡ ~/BnM_Minishell\
		\033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)-\
		-\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m");
		printf("\033[1;33m");
		if (!g_data.cmdline)
			return (0);
		if (g_data.cmdline && *g_data.cmdline)
			add_history(g_data.cmdline);
		check_cmd();
		free (g_data.cmdline);
	}	
	return (0);
}
