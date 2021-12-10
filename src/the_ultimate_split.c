/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   The_ultimate_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:08:30 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/10 12:50:27 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	operators_checker(t_data *data, int *x, int *ops_cnt, int flag)
{
	if (!data->single_qoute_flag && !data->double_qoute_flag)
	{
		if ((data->cmdline[(*x)] == '|' && data->cmdline[(*x) + 1] != '|')
			|| (data->cmdline[(*x)] == '>' && data->cmdline[(*x) + 1] != '>')
			|| (data->cmdline[(*x)] == '<' && data->cmdline[(*x) + 1] != '<'))
		{
			if (!flag)
			{
				(*ops_cnt)++;
			}
		}
		else if ((data->cmdline[(*x)] == '|' && data->cmdline[(*x) + 1] == '|')
			|| (data->cmdline[(*x)] == '>' && data->cmdline[(*x) + 1] == '>')
			|| (data->cmdline[(*x)] == '<' && data->cmdline[(*x) + 1] != '<')
			|| (data->cmdline[(*x)] == '&' && data->cmdline[(*x) + 1] == '&'))
		{
			if (!flag)
			{
				(*ops_cnt)++;
			}
			data->dbl_op_f = 1;
			(*x)++;
		}
	}
}

void	qoutes_checker_3d(t_data *data, int x)
{
	if ((data->cmdline[x] == '\'' || data->cmdline[x] == '"')
		&& !data->single_qoute_flag && !data->double_qoute_flag)
	{
		if (data->cmdline[x] == '\'')
			data->single_qoute_flag = 1;
		else
			data->double_qoute_flag = 1;
		x++;
	}
	if ((data->cmdline[x] == '\'' && data->single_qoute_flag)
		|| (data->cmdline[x] == '"' && data->double_qoute_flag))
	{
		if (data->cmdline[x] == '\'')
			data->single_qoute_flag = 0;
		else
			data->double_qoute_flag = 0;
	}
}

void	alloc_cmd(t_data *data, int *i, int *old_x, int x)
{
	int	j;

	j = 0;
	if (data->dbl_op_f)
		data->sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x));
	else
		data->sep_cmds[*i] = (char *)malloc(sizeof(char) * (x - *old_x) + 1);
	if (!data->sep_cmds[*i])
		ft_exit(data, 1);
	j = 0;
	while (*old_x < x)
	{
		if (data->dbl_op_f && *old_x == x - 2)
		{
			data->dbl_op_f = 0;
			(*old_x) += 2;
			break ;
		}
		data->sep_cmds[*i][j] = data->cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	data->sep_cmds[*i][j] = 0;
	(*old_x)++;
	(*i)++;
}

void	alloc_last_cmd(t_data *data, int *i, int *old_x, int *x)
{
	int	j;

	data->sep_cmds[*i] = (char *)malloc(sizeof(char) * (*x - *old_x) + 1);
	// printf("x - old_x + 1 = %d\n", *x - *old_x + 1);
	j = 0;
	while (*old_x < *x)
	{
		data->sep_cmds[*i][j] = data->cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	// printf("u_sep_cmds[0] = %s\n", data->sep_cmds[0]);
	data->sep_cmds[*i][j] = 0;
	printf("u_sep_cmds[0] = %s\tu_sep_cmds[1] = %s\ti = %d\tu_sep_cmds[i] = %s\n", data->sep_cmds[0], data->sep_cmds[1], *i, data->sep_cmds[*i]);
	(*i)++;
	printf("u_sep_cmds[0] = %s\tu_sep_cmds[1] = %s\ti = %d\n", data->sep_cmds[0], data->sep_cmds[1], *i);
	data->sep_cmds[*i] = 0;
	printf("u_sep_cmds[0] = %s\tu_sep_cmds[1] = %s\ti = %d\tu_sep_cmds[i] = %s\n", data->sep_cmds[0], data->sep_cmds[1], *i, data->sep_cmds[*i]);
}

void	sep_cmds_creator(t_data *data)
{
	int	ops_cnt;
	int	i;
	int	old_x;
	int	x;

	old_x = 0;
	i = 0;
	ops_cnt = 0;
	x = 0;
	while (data->cmdline[x])
	{
		qoutes_checker_3d(data, x);
		operators_checker(data, &x, &ops_cnt, 0);
		if (ops_cnt != i)
			alloc_cmd(data, &i, &old_x, x);
		x++;
	}
	alloc_last_cmd(data, &i, &old_x, &x);
}

void	ultimate_3d_split(t_data *data)
{
	int	x;
	int	ops_cnt;

	x = 0;
	ops_cnt = 0;
	while (data->cmdline[x])
	{
		qoutes_checker_3d(data, x);
		operators_checker(data, &x, &ops_cnt, 0);
		x++;
	}
	data->cmd = (char ***)malloc(sizeof(char **) * ops_cnt + 2);
	data->sep_cmds = (char **)malloc(sizeof(char *) * ops_cnt + 2);
	// printf("ops_count + 2 = %d\n", ops_cnt + 2);
	if (!data->cmd || !data->sep_cmds)
		ft_exit(data, 1);
	sep_cmds_creator(data);
	data->n = 0;
	while (data->n < ops_cnt + 1)
	{
		data->cmd[data->n] = cmd_split(data);
		(data->n)++;
	}
	data->cmd[data->n] = 0;
	data->n = 0;
}
