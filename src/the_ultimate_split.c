/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_ultimate_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:08:30 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/11 02:46:50 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * This function is to check the operators
 * there operators are represented in numbers as following
 * 		1 = |
 *  	2 = >
 * 		3 = <
 * 		4 = ||
 * 		5 = >>
 * 		6 = <<
 * 		7 = &&
 **/
void	operators_checker(t_data *data, int *x, int *ops_cnt, int flag)
{
	if (!data->single_qoute_flag && !data->double_qoute_flag)
	{
		if ((data->cmdline[(*x)] == '|' && data->cmdline[(*x) + 1] != '|')
			|| (data->cmdline[(*x)] == '>' && data->cmdline[(*x) + 1] != '>')
			|| (data->cmdline[(*x)] == '<' && data->cmdline[(*x) + 1] != '<'))
		{
			if (flag)
			{
				if (data->cmdline[(*x)] == '|')
					data->ops_array[data->op_cnt] = 1;
				else if (data->cmdline[(*x)] == '>')
					data->ops_array[data->op_cnt] = 2;
				else if (data->cmdline[(*x)] == '<')
					data->ops_array[data->op_cnt] = 3;
				data->op_cnt++;
			}
			(*ops_cnt)++;
		}
		else if ((data->cmdline[(*x)] == '|' && data->cmdline[(*x) + 1] == '|')
			|| (data->cmdline[(*x)] == '>' && data->cmdline[(*x) + 1] == '>')
			|| (data->cmdline[(*x)] == '<' && data->cmdline[(*x) + 1] == '<')
			|| (data->cmdline[(*x)] == '&' && data->cmdline[(*x) + 1] == '&'))
		{
			if (flag)
			{
				if (data->cmdline[(*x)] == '|')
					data->ops_array[data->op_cnt] = 4;
				else if (data->cmdline[(*x)] == '>')
					data->ops_array[data->op_cnt] = 5;
				else if (data->cmdline[(*x)] == '<')
					data->ops_array[data->op_cnt] = 6;
				else if (data->cmdline[(*x)] == '&')
					data->ops_array[data->op_cnt] = 7;
				data->op_cnt++;
			}
			data->dbl_op_f = 1;
			(*ops_cnt)++;
			(*x)++;
		}
	}
}


/**
 * This function is to check the qoutes for the 3d array split
 **/
void	qoutes_checker_3d(t_data *data, int *x)
{
	if ((data->cmdline[*x] == '\'' || data->cmdline[*x] == '"')
		&& !data->single_qoute_flag && !data->double_qoute_flag)
	{
		if (data->cmdline[*x] == '\'')
			data->single_qoute_flag = 1;
		else
			data->double_qoute_flag = 1;
		(*x)++;
	}
	if ((data->cmdline[*x] == '\'' && data->single_qoute_flag)
		|| (data->cmdline[*x] == '"' && data->double_qoute_flag))
	{
		if (data->cmdline[*x] == '\'')
			data->single_qoute_flag = 0;
		else
			data->double_qoute_flag = 0;
	}
}

/**
 * This function is allocate each command for sep_cmds
 * **/
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
		if (data->dbl_op_f && *old_x == x - 1)
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

/**
 * This function is allocate last command for sep_cmds
 * **/
void	alloc_last_cmd(t_data *data, int *i, int *old_x, int *x)
{
	int	j;

	data->sep_cmds[*i] = (char *)malloc(sizeof(char) * (*x - *old_x) + 1);
	j = 0;
	while (*old_x < *x)
	{
		data->sep_cmds[*i][j] = data->cmdline[*old_x];
		(*old_x)++;
		j++;
	}
	data->sep_cmds[*i][j] = 0;
	(*i)++;
	data->sep_cmds[*i] = 0;
}

/**
 * This function is to get sep_cmds from cmdline
 * **/
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
		qoutes_checker_3d(data, &x);
		operators_checker(data, &x, &ops_cnt, 1);
		data->ops_array[data->op_cnt] = '\0';
		if (ops_cnt != i)
			alloc_cmd(data, &i, &old_x, x);
		x++;
	}
	alloc_last_cmd(data, &i, &old_x, &x);
}

/**
 * This is the ultimate 3d split
 * Nothing to explain It's the best 
 * PEACE
 * **/
void	ultimate_3d_split(t_data *data)
{
	int	x;
	int	ops_cnt;

	x = 0;
	ops_cnt = 0;
	if (!*data->cmdline)
		return ;
	while (data->cmdline[x])
	{
		qoutes_checker_3d(data, &x);
		operators_checker(data, &x, &ops_cnt, 0);
		x++;
	}
	data->cmd = (char ***)malloc(sizeof(char **) * (ops_cnt + 2));
	data->sep_cmds = (char **)malloc(sizeof(char *) * (ops_cnt + 2));
	data->ops_array = (int *)malloc(sizeof(int) * (ops_cnt + 1));
	if (!data->cmd || !data->sep_cmds)
		ft_exit(data, 1);
	sep_cmds_creator(data);
	data->n = 0;
	while (data->n < ops_cnt + 1)
		data->cmd[data->n++] = cmd_split(data);
	data->cmd[data->n] = 0;
	data->n = 0;
	data->op_cnt = 0;
}
