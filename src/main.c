/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/14 12:21:59 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data				data;
	struct sigaction	sig_sig;

	sig_sig.sa_flags = 0;
	sig_sig.sa_mask = 0;
	sig_sig.sa_sigaction = &sig_handler;
	sigaction(SIGINT, &sig_sig, NULL);
	initialize(&data);
	printf("\033[?1049h\033[H");
	while (1)
	{
		data.cmdline = readline(MAC_PROMPT);
		// data.cmdline = "echo hi $_ '' wow > beso || grep we wa << woo >> yes      | hi && trick & yeah";
		if (!data.cmdline)
			ft_exit(&data, 0);
		if (data.cmdline && *data.cmdline)
			add_history(data.cmdline);
		ultimate_3d_split(&data);
		check_cmd(&data);
		free_all(&data);
	}
	return (0);
}
