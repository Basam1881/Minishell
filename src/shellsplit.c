/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:25 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/07 15:33:24 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to set the qoutes flags either to 1 or 0, so we
	can tell if we are inside qoutes at the moment or not
*/
static void	qoutes_checker(int *x, int *i, int *j)
{
	if ((g_data.cmdline[*x] == '\'' || g_data.cmdline[*x] == '"')
		&& !g_data.single_qoute_flag && !g_data.double_qoute_flag)
	{
		if (g_data.cmdline[*x] == '\'')
			g_data.single_qoute_flag = 1;
		else
			g_data.double_qoute_flag = 1;
		(*x)++;
	}
	if ((g_data.cmdline[*x] == '\'' && g_data.single_qoute_flag)
		|| (g_data.cmdline[*x] == '"' && g_data.double_qoute_flag))
	{
		if (g_data.cmdline[*x] == '\'')
			g_data.single_qoute_flag = 0;
		else
			g_data.double_qoute_flag = 0;
	}
	else
	{
		if (g_data.split_flag == 2)
			g_data.cmd[*i][*j] = g_data.cmdline[*x];
		if (g_data.split_flag)
			(*j)++;
	}
	(*x)++;
}

/*
	It's used to either malloc the size for the argument or
	to put null at the end according the to the flag
*/
static void	check_arg_helper(int *i, int *j)
{
	if (g_data.split_flag)
	{
		if (g_data.split_flag == 2)
			g_data.cmd[*i][*j] = 0;
		else
		{
			g_data.cmd[*i] = (char *)malloc(sizeof(char) * (*j) + 1);
			if (!g_data.cmd[*i])
				failed_split(*i);
		}
		(*i)++;
	}
}

/*
	It's used to loop through each argument of any command
	and check the qoutes...etc
*/
static void	check_arg(int *x, int *i)
{
	int		j;

	g_data.single_qoute_flag = 0;
	g_data.double_qoute_flag = 0;
	j = 0;
	if (!g_data.split_flag)
		(*i)++;
	while (g_data.cmdline[*x] && (g_data.cmdline[*x] != ' '
			|| (g_data.cmdline[*x] == ' '
				&& (g_data.single_qoute_flag || g_data.double_qoute_flag))))
		qoutes_checker(x, i, &j);
	check_arg_helper(i, &j);
}

/*
	The function has three integer flags (0, 1 and 2)
	flag 0 will give the number of words (arguments)
	flag 1 will allocate a memory for the words (arguments)
	flag 2 will copy the proper value from the string (cmdline)
	to the arguments you have
*/
static int	split_into_arg(void)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (g_data.cmdline[x])
	{
		if (g_data.cmdline[x] == ' ')
			x++;
		else
			check_arg(&x, &i);
	}
	if (g_data.split_flag == 2)
		g_data.cmd[i] = 0;
	else if (g_data.split_flag == 1)
	{
		g_data.cmd[x] = (char *)malloc(sizeof(char));
		if (!g_data.cmd[x])
			failed_split(x - 1);
	}
	return (i);
}

/*
	It's used to seperate the string (command) into arguments,
	store them into 2d array and return it back
*/
char	**cmd_split(void)
{
	int		words;

	if (!g_data.cmdline)
		return (ft_calloc(1, 1));
	g_data.split_flag = 0;
	words = split_into_arg();
	g_data.cmd = (char **)malloc(sizeof(char *) * words + 1);
	if (!(g_data.cmd))
		return (0);
	g_data.split_flag = 1;
	split_into_arg();
	g_data.split_flag = 2;
	split_into_arg();
	return (g_data.cmd);
}
