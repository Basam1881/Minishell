/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:54 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/05 06:47:55 by mal-guna         ###   ########.fr       */
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

	envsize = ft_strlen2(environ);
	newenv = (char **)malloc(sizeof(char **) * (envsize));

	i = 0;
	j = 0;
	while(environ[i])
	{
		while(v[j] == environ[i][j] && v && environ[i][j] != '=')
			j++;
		if(!v[j] && environ[i][j] == '=')
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
		while(environ[++j])
		{
			newenv[k] = environ[j];
			if(j == i)
				continue ;
			k++;
		}
		newenv[k] = NULL;
		environ = newenv;
	}
}
