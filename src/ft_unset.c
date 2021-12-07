/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:54 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/07 15:33:21 by dfurneau         ###   ########.fr       */
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

	envsize = ft_strlen2(g_data.env);
	newenv = (char **)malloc(sizeof(char **) * (envsize));

	i = 0;
	j = 0;
	while(g_data.env[i])
	{
		while(v[j] == g_data.env[i][j] && v && g_data.env[i][j] != '=')
			j++;
		if(!v[j] && g_data.env[i][j] == '=')
		{
			break;
		}
		i++;
		j = 0;
	}
	if(!(i >= envsize))
	{
		j = -1;
		k = 0;
		while(g_data.env[++j])
		{
			newenv[k] = g_data.env[j];
			if(j == i)
				continue ;
			k++;
		}
		newenv[k] = NULL;
		g_data.env = newenv;
	}
}
