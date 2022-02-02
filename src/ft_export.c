/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:47:51 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 18:06:55 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_export(void)
{
	int	x;
	int	i;

	x = 0;
	while (g_data.environ[x])
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (g_data.environ[x][i] && g_data.environ[x][i] != '=')
		{
			write(1, &g_data.environ[x][i], 1);
			i++;
		}
		if (g_data.environ[x][i] == '=')
			write(1, "=", 1);
		write(1, "\"", 1);
		while (g_data.environ[x][i])
		{
			write(1, &g_data.environ[x][i], 1);
			i++;
		}
		write(1, "\"", 1);
		write(1, "\n", 1);
		x++;
	}
}

int	check_export_args(char *v)
{
	if (v[0] == '=' || ft_isdigit(v[0]))
	{
		ft_putstr_fd("BNM_bash: export : `", 2);
		ft_putstr_fd(v, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(v);
		g_data.exit_status = 1;
		return (1);
	}
	else if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
	{
		if (!allowed_name(v))
		{
			g_data.exit_status = 1;
			ft_putstr_fd("BNM_bash: export : `", 2);
			ft_putstr_fd(v, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		free(v);
		return (1);
	}
	return (0);
}

void	create_new_variable(char *v)
{
	char	**newenv;
	int		i;
	int		envsize;

	i = 0;
	envsize = ft_strlen2(g_data.environ);
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

void	update_current_variable(char *v, char *var_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data.environ[i])
	{
		while (var_name[j] == g_data.environ[i][j]
			&& (var_name && g_data.environ[i][j] != '='))
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

void	ft_export(char *v)
{
	char	*var_name;

	if (check_export_args(v))
		return ;
	var_name = ft_substr(v, 0, ft_chrindex(v, '='));
	if (!allowed_name(var_name))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("BNM_bash: export : `", 2);
		ft_putstr_fd(v, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(v);
		free(var_name);
		return ;
	}
	if (!search_env(var_name))
		create_new_variable(v);
	else
		update_current_variable(v, var_name);
	free(var_name);
	free(v);
	g_data.exit_status = 0;
}
