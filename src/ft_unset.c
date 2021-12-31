/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:54 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/28 16:10:00 by bnaji            ###   ########.fr       */
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

	envsize = ft_strlen2(g_data.environ);
	newenv = (char **)malloc(sizeof(char **) * (envsize));
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
		j = -1;
		k = 0;
		while (g_data.environ[++j])
		{
			newenv[k] = g_data.environ[j];
			if (j == i)
				continue ;
			k++;
		}
		newenv[k] = NULL;
		g_data.environ = newenv;
	}
}
