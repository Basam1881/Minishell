/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:54 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/31 12:39:09 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(char *v)
{
	int		i;
	int		j;
	int		k;
	char	**newenv;
	int		envsize;

	if (!allowed_name(v))
	{
		ft_putstr_fd("BNM bash: unset : ", 2);
		ft_putstr_fd(v, 2);
		ft_putstr_fd(": not a valid identifier", 2);
		ft_putchar_fd('\n', 2);
		free(v);
		g_data.exit_status = 1;
		return ;
	}
	envsize = ft_strlen2(g_data.environ);
	i = 0;
	j = 0;
	while (g_data.environ[i])
	{
		while (v[j] == g_data.environ[i][j] && v && g_data.environ[i][j] != '=')
			j++;
		if (!v[j] && g_data.environ[i][j] == '=')
		{
			break ;
		}
		i++;
		j = 0;
	}
	if (!(i >= envsize))
	{
		newenv = (char **)malloc(sizeof(char **) * (envsize));
		j = -1;
		k = 0;
		while (g_data.environ[++j])
		{
			newenv[k] = ft_strdup(g_data.environ[j]);
			if (j == i)
				continue ;
			k++;
		}
		newenv[k] = NULL;
		free_2d(&g_data.environ);
		g_data.environ = newenv;
	}
	free(v);
}