/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:39:09 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 11:39:10 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_chrindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	search_env(char *var_name)
{
	int		i;
	char	*temp;

	i = 0;
	while (g_data.environ[i])
	{
		temp = ft_substr(g_data.environ[i], 0, \
		ft_chrindex(g_data.environ[i], '='));
		if (!ft_strcmp(var_name, temp))
		{
			free(temp);
			return (1);
		}
		free(temp);
		i++;
	}
	return (0);
}

int	allowed_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]))
		return (0);
	while (name[i])
	{
		if (!((ft_isalnum(name[i]) || name[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}
