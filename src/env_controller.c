/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:31:54 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/22 20:42:46 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_exit(int *x, int *i, int *j)
{
	char	*exit_num;
	int		exit_num_len;
	int		n;

	n = 0;
	exit_num = ft_itoa(g_data.exit_status);
	exit_num_len = ft_strlen(exit_num);
	if (g_data.split_flag)
	{
		if (g_data.split_flag == 1)
			*j += exit_num_len;
		else
			while (n < exit_num_len)
				g_data.cmd[g_data.n][*i][(*j)++] = exit_num[n++];
		(*x) += 2;
	}
}

static int	ft_strlen_to_space(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]))
		return (-1);
	while (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
		i++;
	return (i);
}

static void	no_env_in_no_qoutes(char *new_s, int *i, int *j, int *x)
{
	if (!new_s)
	{
		if (!g_data.double_qoute_flag && !g_data.single_qoute_flag && g_data
			.sep_cmds[g_data.n][*x - 1] == ' ' && (g_data.sep_cmds[g_data.n][*x
				+ ft_strlen_to_space(&g_data.sep_cmds[g_data.n][*x + 1])
								+ 1] == ' '|| !g_data.sep_cmds[g_data.n][*x +
				ft_strlen_to_space(&g_data.sep_cmds[g_data.n][*x + 1]) + 1]))
		{
			(*i)--;
			g_data.no_env_arg_flag = 1;
		}
		else
			(*j)--;
	}
}

char	*get_expnd_val(char *var_name)
{
	int		i;
	char	*temp;
	char	*val;

	i = 0;
	while (g_data.environ[i])
	{
		temp = ft_substr(g_data.environ[i], 0, ft_chrindex(g_data.environ[i], '='));
		if (!ft_strcmp(var_name, temp))
		{
			val = ft_strdup(ft_strchr(g_data.environ[i], '=') + 1);
			free(temp);
			return (val);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

/**
 * TODO: Replace getenv to keep things updated
 * TODO: fix it so wwherever you find non non characters you 
 * 		will print from there insted of sikpping
**/
void	env_checker(int *x, int *i, int *j)
{
	int		new_len;
	int		old_len;
	char	*old_s;
	char	*new_s;
	int		n;

	old_len = ft_strlen_to_space(&g_data.sep_cmds[g_data.n][*x + 1]);
	if (!old_len)
	{
		if (g_data.split_flag == 2)
			g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
		return ;
	}
	else if (old_len == -1)
	{
		(*x) += 2;
		g_data.digit_env = 1;
		return ;
	}
	old_s = ft_substr(&g_data.sep_cmds[g_data.n][*x + 1], 0, old_len);
	new_s = get_expnd_val(old_s);
	if (new_s)
	{
		if ( g_data.split_flag)
		{
			new_len = ft_strlen(new_s);
			if (g_data.split_flag == 1)
				*j += new_len;
			else
			{
				n = 0;
				while (n < new_len)
					g_data.cmd[g_data.n][*i][(*j)++] = new_s[n++];
			}
			(*j)--;
		}
	}
	else
		no_env_in_no_qoutes(new_s, i, j, x);
	// printf("start: |%c|\t\tend: |%c|\n", g_data.sep_cmds[g_data.n][*x], g_data.sep_cmds[g_data.n][*x + old_len]);
	(*x) += old_len;
	return ;
}
