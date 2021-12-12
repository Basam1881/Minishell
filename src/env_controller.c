/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:29:09 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/11 15:14:38 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strlen_to_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i])
		i++;
	return (i);
}

static void	no_env_in_no_qoutes(t_data *data, char *new_s, int *i, int *x)
{
	if (!new_s)
	{
		if (!data->double_qoute_flag && !data->single_qoute_flag && data
			->sep_cmds[data->n][*x - 1] == ' ' && data->sep_cmds[data->n][*x
				+ ft_strlen_to_space(&data
				->sep_cmds[data->n][*x + 1]) + 1] == ' ')
		{
			(*i)--;
			data->no_env_arg_flag = 1;
		}
	}
}

void	env_checker(t_data *data, int *x, int *i, int *j)
{
	int		new_len;
	int		old_len;
	char	*old_s;
	char	*new_s;
	int		n;

	old_len = ft_strlen_to_space(&data->sep_cmds[data->n][*x + 1]);
	old_s = ft_substr(&data->sep_cmds[data->n][*x + 1], 0, old_len);
	new_s = getenv(old_s);
	if (new_s && data->split_flag)
	{
		new_len = ft_strlen(new_s);
		if (data->split_flag == 1)
			*j += new_len;
		else
		{
			n = 0;
			while (n < new_len)
				data->cmd[data->n][*i][(*j)++] = new_s[n++];
		}
		(*j)--;
	}
	no_env_in_no_qoutes(data, new_s, i, x);
	*x += old_len;
	return ;
}
