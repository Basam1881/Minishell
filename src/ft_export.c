/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:51 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/17 02:37:33 by bnaji            ###   ########.fr       */
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
	printf("|%s|\n", v);

	if ((size_t)ft_chrindex(v, '=') == ft_strlen(v)-1)
	{		
		return ;
	}

	var_name = ft_substr(v, 0, ft_chrindex(v, '='));
	printf("var_name = |%s|\n", var_name);
	envsize = ft_strlen2(g_data.environ);
	newenv = (char **)malloc(sizeof(char **) * (envsize + 2));
	var = getenv(var_name);
	if (!var)
	{
		printf("var = |%s|\n", var);
		i = 0;
		while (g_data.environ[i])
		{
			newenv[i] = g_data.environ[i];
			i++;
		}
		newenv[i] = v;
		i++;
		newenv[i] = NULL;
		g_data.environ = newenv;
	}
	else
	{
		printf("here\n");
		i = 0;
		j = 0;
		while (g_data.environ[i])
		{
			while (var_name[j] == g_data.environ[i][j] && var_name && g_data.environ[i][j] != '=')
				j++;
			if (!var_name[j] && g_data.environ[i][j] == '=')
			{
				g_data.environ[i] = v;
				break ;
			}
			i++;
			j = 0;
		}
	}
}
