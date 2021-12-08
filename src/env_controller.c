/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:29:09 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/08 19:30:18 by dfurneau         ###   ########.fr       */
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

void	env_replacer(t_data *data, int *x,int *i, int *j)
{
	int		new_len;
	char	*old_s;
	char	*new_s;
	int		n;

	old_s = ft_substr(&data->cmdline[*x + 1], 0, ft_strlen_to_space(&data->cmdline[*x + 1]));
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
			{
				data->cmd[*i][*j] = new_s[n];
				(*j)++;
				n++;
			}
		}
		(*j)--;
	}
	// else if(!new_s !data->split_flag)
	// 	if (!data->double_qoute_flag && !data->single_qoute_flag && data->cmdline[*x -1] == ' ')
	// 		(*i)--;
	*x += ft_strlen_to_space(&data->cmdline[*x + 1]);
	return ;
}
