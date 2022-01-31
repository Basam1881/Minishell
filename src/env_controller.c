/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:31:54 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/31 11:00:05 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_exit(int i)
{
	char	*exit_num;
	char	*tmp;
	int		exit_num_len;
	int		n;
	int		k;
	int		m;
	int		x;
	int		z;

	n = 0;
	x = 0;
	exit_num = ft_itoa(g_data.exit_status);
	exit_num_len = ft_strlen(exit_num);
	while (g_data.cmd[i][x])
	{
		z = 0;
		while (g_data.cmd[i][x][z])
		{
			if (g_data.cmd[i][x][z] == '$' && g_data.cmd[i][x][z + 1] == '?')
			{
				if (g_data.question_array[g_data.question_cnt] == 1)
				{
					tmp = ft_strdup(g_data.cmd[i][x]);
					free(g_data.cmd[i][x]);
					g_data.cmd[i][x] = (char *)malloc(sizeof(char) * ((ft_strlen(tmp) + exit_num_len - 2) + 1));
					n = 0;
					while (n < z)
					{
						g_data.cmd[i][x][n] = tmp[n];
						n++;
					}
					k = n + 2;
					m = 0;
					while (exit_num[m])
						g_data.cmd[i][x][n++] = exit_num[m++];
					while (tmp[k])
					{
						g_data.cmd[i][x][n] = tmp[k++];
						n++;
					}
					g_data.cmd[i][x][n] = '\0';
					free(tmp);
				}
				g_data.question_cnt++;
			}
			z++;
		}
		x++;
	}
	free(exit_num);
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

	if (g_data.n)
	{
		if (g_data.ops_array[g_data.n - 1] == 6)
		{
			if (g_data.split_flag == 2)
				g_data.cmd[g_data.n][*i][*j] = g_data.sep_cmds[g_data.n][*x];
			return ;
		}	
	}
	old_len = ft_strlen_to_space(&g_data.sep_cmds[g_data.n][*x + 1]);
	if (!old_len)
	{
		if ((!g_data.double_qoute_flag && !g_data.single_qoute_flag) && (g_data.sep_cmds[g_data.n][*x + 1] == '\'' || g_data.sep_cmds[g_data.n][*x + 1] == '"'))
		{
			(*x)++;
			g_data.digit_env = 1;
		}
		else if (g_data.split_flag == 2)
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
	free (old_s);
	if (new_s)
	{
		if (g_data.split_flag)
		{
			new_len = ft_strlen(new_s);
			if (g_data.split_flag == 1)
				*j += new_len;
			else
			{
				n = 0;
				while (n < new_len)
				{
					g_data.cmd[g_data.n][*i][(*j)++] = new_s[n];
					n++;
				}
			}
			(*j)--;
		}
	}
	else
		no_env_in_no_qoutes(new_s, i, j, x);
	free(new_s);
	(*x) += old_len;
	return ;
}
