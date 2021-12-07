/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:25 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/07 18:13:26 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to set the qoutes flags either to 1 or 0, so we
	can tell if we are inside qoutes at the moment or not
*/
static void	qoutes_checker(t_data *data, int *x, int *i, int *j)
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
	else
	{
		if (data->split_flag == 2)
			data->cmd[*i][*j] = data->cmdline[*x];
		if (data->split_flag)
			(*j)++;
	}
	(*x)++;
}

/*
	It's used to either malloc the size for the argument or
	to put null at the end according the to the flag
*/
static void	check_arg_helper(t_data *data, int *i, int *j)
{
	if (data->split_flag)
	{
		if (data->split_flag == 2)
			data->cmd[*i][*j] = 0;
		else
		{
			data->cmd[*i] = (char *)malloc(sizeof(char) * (*j) + 1);
			if (!data->cmd[*i])
				failed_split(data, *i);
		}
		(*i)++;
	}
}

/*
	It's used to loop through each argument of any command
	and check the qoutes...etc
*/
static void	check_arg(t_data *data, int *x, int *i)
{
	int		j;

	data->single_qoute_flag = 0;
	data->double_qoute_flag = 0;
	j = 0;
	if (!data->split_flag)
		(*i)++;
	while (data->cmdline[*x] && (data->cmdline[*x] != ' '
			|| (data->cmdline[*x] == ' '
				&& (data->single_qoute_flag || data->double_qoute_flag))))
		qoutes_checker(data, x, i, &j);
	check_arg_helper(data, i, &j);
}

/*
	The function has three integer flags (0, 1 and 2)
	flag 0 will give the number of words (arguments)
	flag 1 will allocate a memory for the words (arguments)
	flag 2 will copy the proper value from the string (cmdline)
	to the arguments you have
*/
static int	split_into_arg(t_data *data)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (data->cmdline[x])
	{
		if (data->cmdline[x] == ' ')
			x++;
		else
			check_arg(data, &x, &i);
	}
	if (data->split_flag == 2)
		data->cmd[i] = 0;
	else if (data->split_flag == 1)
	{
		data->cmd[x] = (char *)malloc(sizeof(char));
		if (!data->cmd[x])
			failed_split(data, x - 1);
	}
	return (i);
}

/*
	It's used to seperate the string (command) into arguments,
	store them into 2d array and return it back
*/
char	**cmd_split(t_data *data)
{
	int		words;

	if (!data->cmdline)
		return (ft_calloc(1, 1));
	data->split_flag = 0;
	words = split_into_arg(data);
	data->cmd = (char **)malloc(sizeof(char *) * words + 1);
	if (!(data->cmd))
		return (0);
	data->split_flag = 1;
	split_into_arg(data);
	data->split_flag = 2;
	split_into_arg(data);
	return (data->cmd);
}
