/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/07 16:02:55 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
void	failed_split(t_data *data, int n)
{
	while (n >= 0)
	{
		free(data->cmd[n]);
		n--;
	}
	free(data->cmd);
	free(data->cmdline);
	exit (1);
}

void	error(t_data *data, int n)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
	free(data->cmdline);
	exit(n);
}
