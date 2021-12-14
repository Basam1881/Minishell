/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:23:26 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/14 12:17:37 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize(t_data *data)
{
	data->cmdline = NULL;
	data->cmd = NULL;
	data->sep_cmds = NULL;
	data->ops_array = NULL;
	data->no_env_arg_flag = 0;
	data->double_qoute_flag = 0;
	data->single_qoute_flag = 0;
	data->dbl_op_f = 0;
	data->n = 0;
	data->op_cnt = 0;
}

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
void	failed_split(t_data *data, int n)
{
	int	i;

	i = 0;
	while (data->n >= 0)
	{
		while (n >= 0)
		{
			free(data->cmd[data->n][n]);
			n--;
		}
		free(data->cmd[data->n]);
		data->n--;
	}
	free (data->cmd);
	while (data->sep_cmds[i])
		free (data->sep_cmds[i++]);
	free (data->sep_cmds);
	free(data->cmdline);
	exit (1);
}

void	free_big_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->cmd)
	{
		while (data->cmd[i])
		{
			j = 0;
			while (data->cmd[i][j])
				free (data->cmd[i][j++]);
			free (data->cmd[i++]);
		}
		free (data->cmd);
	}
	i = 0;
	if (data->sep_cmds)
	{
		while (data->sep_cmds[i])
			free (data->sep_cmds[i++]);
		free (data->sep_cmds);
	}
}

void	free_all(t_data *data)
{
	if (!data->cmdline)
		return ;
	if (!*data->cmdline)
	{
		free(data->cmdline);
		return ;
	}
	free_big_data(data);
	free(data->cmdline);
	if (data->ops_array)
		free(data->ops_array);
	initialize(data);
}

void	ft_exit(t_data *data, int n)
{
	free_all(data);
	if (n == 1)
	{
		perror("Error. (Check your malloc functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	else if (n == 2)
	{
		perror("Error. (Check your read functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	else if (n == 3)
	{
		perror("Error. (Check your write functions)");
		printf("zsh: %s\n", strerror(errno));
		printf("exit with code: %d\n", errno);
	}
	exit(n);
}
