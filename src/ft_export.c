/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:51 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/07 15:33:18 by dfurneau         ###   ########.fr       */
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

void	ft_export(char *v)
{
	int		i;
	int		j;
	char	**newenv;
	int		envsize;
	char	*var_name;
	char	*var;

	if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
	{
		return ;
	}
	var_name = ft_substr(v, 0, ft_chrindex(v, '='));
	envsize = ft_strlen2(g_data.env);
	newenv = (char **)malloc(sizeof(char **) * (envsize + 2));
	var = getenv(var_name);
	if (!var)
	{
		i = 0;
		while (g_data.env[i])
		{
			newenv[i] = g_data.env[i];
			i++;
		}
		newenv[i] = v;
		i++;
		newenv[i] = NULL;
		g_data.env = newenv;
	}
	else
	{
		i = 0;
		j = 0;
		while (g_data.env[i])
		{
			while (var_name[j] == g_data.env[i][j] && var_name && g_data.env[i][j] != '=')
				j++;
			if (!var_name[j] && g_data.env[i][j] == '=')
			{
				g_data.env[i] = v;
				break ;
			}
			i++;
			j = 0;
		}
	}
}
