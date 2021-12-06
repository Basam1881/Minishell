/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/06 16:35:26 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data	data;

	printf("\033[?1049h\033[H");
	while (1)
	{
		printf("\033[m");
		data.cmdline = readline("\033[1;34m⚡⚡ ~/BnM_Minishell\
		\033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)-\
		-\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m");
		printf("\033[1;33m");
		if (!data.cmdline)
			return (0);
		if (data.cmdline && *data.cmdline)
			add_history(data.cmdline);
		check_cmd(&data);
		free (data.cmdline);
	}	
	return (0);
}
