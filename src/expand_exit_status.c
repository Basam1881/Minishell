/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:29:09 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 18:43:16 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand_exit(int i, int z, int x, char *exit_num)
{
	char	*tmp;
	int		k;
	int		m;
	int		n;

	tmp = ft_strdup(g_data.cmd[i][x]);
	free(g_data.cmd[i][x]);
	g_data.cmd[i][x] = (char *)malloc(sizeof(char)
			* ((ft_strlen(tmp) + ft_strlen(exit_num) - 2) + 1));
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
		g_data.cmd[i][x][n++] = tmp[k++];
	g_data.cmd[i][x][n] = '\0';
	free(tmp);
}

void	env_exit(int i)
{
	char	*exit_num;
	int		x;
	int		z;

	x = 0;
	exit_num = ft_itoa(g_data.exit_status);
	while (g_data.cmd[i][x])
	{
		z = 0;
		while (g_data.cmd[i][x][z])
		{
			if (g_data.cmd[i][x][z] == '$' && g_data.cmd[i][x][z + 1] == '?')
			{
				if (g_data.q_array[g_data.question_cnt] == 1)
					expand_exit(i, z, x, exit_num);
				g_data.question_cnt++;
			}
			z++;
		}
		x++;
	}
	free(exit_num);
}
