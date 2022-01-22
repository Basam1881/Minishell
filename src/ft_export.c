/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:51 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/22 21:14:09 by bnaji            ###   ########.fr       */
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

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int		search_env(char *var_name)
{
	int	i;
	char *temp;

	i = 0;
	while(g_data.environ[i])
	{
		temp = ft_substr(g_data.environ[i], 0, ft_chrindex(g_data.environ[i], '='));
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
void	ft_export(char *v)
{
	int		i;
	int		j;
	char	**newenv;
	int		envsize;
	char	*var_name;

	if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
	{
		free(v);
		return;
	}
	var_name = ft_substr(v, 0, ft_chrindex(v, '='));
	envsize = ft_strlen2(g_data.environ);

	if (!search_env(var_name))
	{
		i = 0;
		newenv = (char **)malloc(sizeof(char **) * (envsize + 2));
		while (g_data.environ[i])
		{
			newenv[i] = ft_strdup(g_data.environ[i]);
			i++;
		}
		newenv[i] = ft_strdup(v);
		i++;
		newenv[i] = NULL;
		free_2d(&g_data.environ);
		g_data.environ = newenv;
	}
	else
	{
		i = 0;
		j = 0;
		while (g_data.environ[i])
		{
			while (var_name[j] == g_data.environ[i][j] && var_name && g_data.environ[i][j] != '=')
				j++;
			if (!var_name[j] && g_data.environ[i][j] == '=')
			{
				free(g_data.environ[i]);
				g_data.environ[i] = NULL;
				g_data.environ[i] = ft_strdup(v);
				break ;
			}
			i++;
			j = 0;
		}
	}
	free(var_name);
	free(v);
}