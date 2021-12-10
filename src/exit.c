/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/10 07:23:53 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize(t_data *data)
{
	data->cmdline = NULL;
	data->cmd = NULL;
	data->sep_cmds = NULL;
	data->no_env_arg_flag = 0;
	data->double_qoute_flag = 0;
	data->single_qoute_flag = 0;
	data->dbl_op_f = 0;
}

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

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	free(data->cmdline);
	if (!data->cmd)
		return ;
	while (data->cmd[i])
	{
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
}

void	ft_exit(t_data *data, int n)
{
	free_all(data);
	exit(n);
}
