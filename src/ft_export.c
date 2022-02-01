/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:51 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/01 20:37:18 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_export()
{
	int	x;
	int i;

	x = 0;
	while (g_data.environ[x])
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while(g_data.environ[x][i] && g_data.environ[x][i] != '=')
		{
			write(1, &g_data.environ[x][i], 1);
			i++;
		}
		if(	g_data.environ[x][i] == '=')
			write(1, "=", 1);
		write(1, "\"", 1);
		while(g_data.environ[x][i])
		{
			write(1, &g_data.environ[x][i], 1);
			i++;
		}
		write(1, "\"", 1);
		write(1, "\n", 1);
		x++;
	}
}
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
int	allowed_name(char *name)
{
	int i;

	i = 0;
	if(ft_isdigit(name[i]))
		return (0);
	while(name[i])
	{
		if(!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
void	ft_export(char *v)
{
	int		i;
	int		j;
	char	**newenv;
	int		envsize;
	char	*var_name;

	if (v[0] == '=' || ft_isdigit(v[0]))
	{
		ft_putstr_fd("BNM_bash: export : `", 2);
		ft_putstr_fd(v, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(v);
		g_data.exit_status = 1;
		return ;
	}
	else if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
	{
		return ;
	}
	var_name = ft_substr(v, 0, ft_chrindex(v, '='));
	if (!allowed_name(var_name))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("BNM_bash: export : `", 2);
		ft_putstr_fd(v, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(v);
		free(var_name);
		return;
	}
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
	g_data.exit_status = 0;

}