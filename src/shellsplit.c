/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:25 by dfurneau          #+#    #+#             */
/*   Updated: 2022/01/13 16:45:34 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * It's used to set the qoutes flags either to 1 or 0, so we 
 * can tell if we are inside qoutes at the moment or not
 * TODO: fix the condition for the enviroment variables to check if after the name is not digit nor character nor underscore
 * TODO: add a flag to ignore the (*) if it's inside qoutes
**/
static void	qoutes_checker(int *x, int *i, int *j)
{
	if ((g_data.sep_cmds[g_data.n][*x] == '\'' && g_data.single_qoute_flag)
		|| (g_data.sep_cmds[g_data.n][*x] == '"' && g_data.double_qoute_flag))
	{
		if (g_data.sep_cmds[g_data.n][*x] == '\'')
			g_data.single_qoute_flag = 0;
		else
			g_data.double_qoute_flag = 0;
	}
	else
	{
		if (g_data.sep_cmds[g_data.n][*x] == '$' && g_data.sep_cmds[g_data
				.n][*x + 1] == '?' && !g_data.single_qoute_flag)
			env_exit(x, i, j);
		if ((g_data.sep_cmds[g_data.n][*x] == '$' && g_data.sep_cmds[g_data
				.n][*x + 1] && g_data.sep_cmds[g_data.n][*x + 1] != ' '
				&& !g_data.single_qoute_flag && !g_data.double_qoute_flag)
			|| (g_data.sep_cmds[g_data.n][*x] == '$' && g_data.sep_cmds[g_data
			.n][*x + 1] && g_data.sep_cmds[g_data.n][*x + 1] != ' ' && g_data
			.sep_cmds[g_data.n][*x + 1] != '"' && !g_data.single_qoute_flag
				&& g_data.double_qoute_flag))
			env_checker(x, i, j);
		else if (g_data.split_flag == 2)
			g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
		if (g_data.split_flag)
			(*j)++;
	}
	(*x)++;
}

/**
*	It's used to either malloc the size for the argument or
*	to put null at the end according the to the flag
**/
static int	check_arg_helper(int *i, int *j)
{
	if (g_data.split_flag)
	{
		if (g_data.split_flag == 2 && !g_data.no_env_arg_flag)
			g_data.cmd[g_data.n][*i][*j] = 0;
		else if (g_data.split_flag == 1 && !g_data.no_env_arg_flag)
		{
			g_data.cmd[g_data.n][*i] = (char *)malloc(sizeof(char) * (*j) + 1);
			if (!g_data.cmd[g_data.n][*i])
			{
				failed_split(*i);
				return (1);
			}
		}
		(*i)++;
	}
	return (0);
}

/**
*	It's used to loop through each argument of any command
*	and check the qoutes...etc
**/
static int	check_arg(int *x, int *i)
{
	int		j;

	g_data.single_qoute_flag = 0;
	g_data.double_qoute_flag = 0;
	j = 0;
	if (!g_data.split_flag)
		(*i)++;
	while (g_data.sep_cmds[g_data.n][*x] && (g_data.sep_cmds[g_data.n][*x] != ' '
			|| (g_data.sep_cmds[g_data.n][*x] == ' '
				&& (g_data.single_qoute_flag || g_data.double_qoute_flag))))
	{
		if ((g_data.sep_cmds[g_data.n][*x] == '\'' || g_data.sep_cmds[g_data.n][*x]
			== '"') && !g_data.single_qoute_flag && !g_data.double_qoute_flag)
		{
			if (g_data.sep_cmds[g_data.n][*x] == '\'')
				g_data.single_qoute_flag = 1;
			else
				g_data.double_qoute_flag = 1;
			(*x)++;
		}
		qoutes_checker(x, i, &j);
	}
	if (check_arg_helper(i, &j))
		return (1);
	g_data.no_env_arg_flag = 0;
	return (0);
}

/**
 * The function has three integer flags (0, 1 and 2)
 * flag 0 will give the number of words (arguments)
 * flag 1 will allocate a memory for the words (arguments)
 * flag 2 will copy the proper value from the string (sep_cmds)
 * to the arguments you have
 **/
static int	split_into_arg(void)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (g_data.sep_cmds[g_data.n][x])
	{
		if (g_data.sep_cmds[g_data.n][x] == ' ')
			x++;
		else
		{
			if (check_arg(&x, &i))
				return (-1);
		}
	}
	if (g_data.split_flag == 2)
		g_data.cmd[g_data.n][i] = NULL;
	return (i);
}

/**
*	It's used to seperate the string (command) into arguments,
*	store them into 2d array and return it back
**/
char	**cmd_split(void)
{
	int		words;

	if (!*g_data.sep_cmds[g_data.n])
	{
		g_data.cmd[g_data.n] = (char **)malloc(sizeof(char *) * 2);
		if (!(g_data.cmd[g_data.n]))
			return (NULL);
		g_data.cmd[g_data.n][0] = (char *)malloc(sizeof(char));
		if (!(g_data.cmd[g_data.n]))
			return (NULL);
		g_data.cmd[g_data.n][0][0] = '\0';
		g_data.cmd[g_data.n][1] = NULL;
		return (g_data.cmd[g_data.n]);
	}
	g_data.split_flag = 0;
	words = split_into_arg();
	g_data.cmd[g_data.n] = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(g_data.cmd[g_data.n]))
		return (NULL);
	g_data.split_flag = 1;
	if (split_into_arg() == -1)
		return (NULL);
	g_data.split_flag = 2;
	split_into_arg();
	return (g_data.cmd[g_data.n]);
}
