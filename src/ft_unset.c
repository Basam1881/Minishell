/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:54 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/27 20:27:40 by mal-guna         ###   ########.fr       */
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
		ft_putstr_fd("unset : ", 2);
		ft_putstr_fd(v, 2);
		ft_putstr_fd(": Invalid", 2);
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