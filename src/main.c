/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/04 05:24:15 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_quotes(char *cmd)
{
	int i;
	char *res;
	int	k;
	char q;
	int j[ft_strlen(cmd)];
	int size;

	k = 0;
	size = 0;
	res = ft_strdup("");
	printf("dd |%s|\n", cmd);
	
	while(cmd[i])
	{
		if(cmd[i] == 34 || cmd[i] == 39 )
		{
			printf("am in loop\n");
			q = cmd[i];
			j[k++] = i;
			i++;
			while(cmd[i] && cmd[i] != q)
				i++;
			if (!cmd[i])
				break;
			j[k++] = i;
			size++;
		}
		i++;
	}
	k = 0;
	printf("|%d| |%d|\n", j[0], j[1]);
	if(size >= 1)
	{
		if (j[0] != 0)
			res = ft_strjoin(res, ft_substr(cmd, 0, j[0]));
		while(size != 0)
		{
			res = ft_strjoin(res, ft_substr(cmd, j[k] + 1, j[k+1] - 1));
			k++;
			size--;
		}
	}
	return (res);
}

int	main(void)
{
	char	*cmd;

	printf("\033[?1049h\033[H");
	while (1)
	{
		cmd = readline("\033[1;34m⚡⚡ ~/BnM_Minishell \033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)--\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m");
		if (!cmd)
			return (0);
		if (ft_strchr(cmd, 34) || ft_strchr(cmd, 39))
			cmd = handle_quotes(cmd);
		if (cmd && *cmd)
			add_history(cmd);
		check_cmd(cmd);
		free (cmd);
	}	
	return (0);
}
