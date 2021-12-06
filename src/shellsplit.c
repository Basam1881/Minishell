/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:25 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/06 12:49:21 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	It's used to free the 2d array we have in case of a failed malloc
*/
static void	ft_free(char **str, int n)
{
	while (n >= 0)
	{
		if (str[n] != NULL)
			free(str[n]);
		n--;
	}
	free(str);
	exit (1); // you should have an error function that will free everything then exit
}

/*
	It's used to set the qoutes flags either to 1 or 0, so we
	can tell if we are inside qoutes at the moment or not
*/
static void	qoutes_checker(char **str, char *s, int *x, int *single_qoute, int *double_qoute, int flag, int *i, int *j)
{
	if ((s[*x] == '\'' || s[*x] == '"') && !*single_qoute && !*double_qoute)
	{
		if (s[*x] == '\'')
			*single_qoute = 1;
		else
			*double_qoute = 1;
		(*x)++;
	}
	if ((s[*x] == '\'' && *single_qoute) || (s[*x] == '"' && *double_qoute))
	{
		if (s[*x] == '\'')
			*single_qoute = 0;
		else
			*double_qoute = 0;
	}
	else
	{
		if (flag == 2)
			str[*i][*j] = s[*x];
		if (flag)
			(*j)++;
	}
	(*x)++;
}

/*
	It's used to either malloc the size for the argument or
	to put null at the end according the to the flag
*/
static void	check_arg_helper(char **str, int *i, int *j, int flag)
{
	if (flag)
	{
		if (flag == 2)
			str[*i][*j] = 0;
		else
		{
			str[*i] = (char *)malloc(sizeof(char) * (*j) + 1);
			if (!str[*i])
				ft_free(str, *i);
		}
		(*i)++;
	}
}

/*
	It's used to loop through each argument of any command
	and check the qoutes...etc
*/
static void	check_arg(char **str, char *s, int flag, int *x, int *i)
{
	int		j;
	int		single_qoute;
	int		double_qoute;

	single_qoute = 0;
	double_qoute = 0;
	j = 0;
	if (!flag)
		(*i)++;
	while (s[*x] && (s[*x] != ' ' || (s[*x] == ' '
				&& (single_qoute || double_qoute))))
		qoutes_checker(str, s, x, &single_qoute, &double_qoute, flag, i, &j);
	check_arg_helper(str, i, &j, flag);
}

	/*
	The function has three integer flags (0, 1 and 2)
	flag 0 will give the number of words (arguments)
	flag 1 will allocate a memory for the words (arguments)
	flag 2 will copy the proper value from the string (cmdline)
	to the arguments you have
*/
static int	split_into_arg(char **str, char *s, int flag)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] == ' ')
			x++;
		else
			check_arg(str, s, flag, &x, &i);
	}
	if (flag == 2)
		str[i] = 0;
	else if (flag == 1)
	{
		str[x] = (char *)malloc(sizeof(char));
		if (!str[x])
			ft_free(str, x);
	}
	return (i);
}

/*It's used to seperate the string (command) into arguments,
	store them into 2d array and return it back*/
char	**cmd_split(char *cmdline)
{
	char	**str;
	int		words;

	if (!cmdline)
		return (ft_calloc(1, 1));
	words = split_into_arg(NULL, (char *)cmdline, 0);
	str = (char **)malloc(sizeof(char *) * words + 1);
	if (!(str))
		return (0);
	split_into_arg(str, (char *)cmdline, 1);
	split_into_arg(str, (char *)cmdline, 2);
	return (str);
}
