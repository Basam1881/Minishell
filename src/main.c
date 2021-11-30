/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/11/30 04:06:43 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*cmd;

	printf("\033[?1049h\033[H");
	while (1)
	{
		cmd = readline("\033[1;34m⚡⚡ ~/BnM/Minishell $-> \033[1;37m");
		if (!cmd)
			return (0);
		if (cmd && *cmd)
			add_history(cmd);
		check_cmd(cmd);
		free (cmd);
	}	
	return (0);
}
