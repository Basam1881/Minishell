/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/05 09:55:34 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*cmd;

	printf("\033[?1049h\033[H");
	while (1)
	{
		printf("\033[m");
		cmd = readline("BnM_Minishell - $>");
		printf("cmd = <echo \"hi\">\n");
		printf("\033[1;33m");
		if (!cmd)
			return (0);
		if (cmd && *cmd)
			add_history(cmd);
		check_cmd(cmd);
		free (cmd);
	}	
	return (0);
}
