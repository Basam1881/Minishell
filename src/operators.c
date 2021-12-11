/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:02:19 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/11 15:12:39 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ops_assigner(t_data *data, int *x, int flag)
{
	if (flag == 1)
	{
		if (data->cmdline[(*x)] == '|')
			data->ops_array[data->op_cnt] = 1;
		else if (data->cmdline[(*x)] == '>')
			data->ops_array[data->op_cnt] = 2;
		else if (data->cmdline[(*x)] == '<')
			data->ops_array[data->op_cnt] = 3;
		data->op_cnt++;
	}
	else
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
}

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
				ops_assigner(data, x, 1);
			(*ops_cnt)++;
		}
		else if ((data->cmdline[(*x)] == '|' && data->cmdline[(*x) + 1] == '|')
			|| (data->cmdline[(*x)] == '>' && data->cmdline[(*x) + 1] == '>')
			|| (data->cmdline[(*x)] == '<' && data->cmdline[(*x) + 1] == '<')
			|| (data->cmdline[(*x)] == '&' && data->cmdline[(*x) + 1] == '&'))
		{
			if (flag)
				ops_assigner(data, x, 1);
			data->dbl_op_f = 1;
			(*ops_cnt)++;
			(*x)++;
		}
	}
}
