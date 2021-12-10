/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/11 02:20:24 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data	data;
	int		i;

	initialize(&data);
	printf("\033[?1049h\033[H");
	while (1)
	{
		data.cmdline = readline("\033[1;34m⚡⚡ ~/BnM_Minishell\
\033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)-\
-\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m");
		// data.cmdline = "echo hi $LESS '' wow > beso || grep we wa << woo >> yes      | hi && trick & yeah";
		if (!data.cmdline)
			ft_exit(&data, 0);
		if (data.cmdline && *data.cmdline)
			add_history(data.cmdline);
		ultimate_3d_split(&data);
		check_cmd(&data);
		i = 0;
		// printf("data.cmdline = |%s|\n", data.cmdline);
		if (*data.cmdline)
			free_all(&data);
		else
		{
			free (data.cmdline);
			data.cmdline = NULL;
		}
	}
	free_all(&data);
	return (0);
}
