/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/02 15:54:29 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*cmd;

	printf("\033[?1049h\033[H");
	while (1)
	{
		cmd = readline("\033[1;34m⚡⚡ ~/BnM_Minishell \033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)--\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m");
		if (!cmd)
			return (0);
		if (cmd && *cmd)
			add_history(cmd);
		check_cmd(cmd);
		free (cmd);
	}	
	return (0);
}
