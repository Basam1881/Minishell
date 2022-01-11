/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:15:01 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/11 16:45:22 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: add errors and make it for any n of commands
 */
void	ft_cd(void)
{
	int		i;
	char	*tmp;

	if (g_data.cmd[g_data.y][2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(g_data.cmd[g_data.y][1], 2);
		ft_putchar_fd('\n', 2);
		g_data.exit_status = 1;
		return ;
	}
	if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
		ft_putstr_fd("failure in updating the environment variable: OLDPWD", 2);
	i = chdir(g_data.cmd[g_data.y][1]);
	if (!i)
	{
		tmp = ft_strjoin_moa("OLDPWD=", g_data.pwd_dir_path);
		ft_export(tmp);
		free(tmp);
		if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
			ft_putstr_fd("failure in updating the environment variable: PWD", 2);
		tmp = ft_strjoin_moa("PWD=", g_data.pwd_dir_path);
		ft_export(tmp);
		free(tmp);
	}
	else if (i == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_data.cmd[g_data.y][1], 2);
		ft_putchar_fd('\n', 2);
		g_data.exit_status = 1;
		return ;
	}
	g_data.exit_status = 0;
}

void	ft_echo(void)
{
	int	n_flag;
	int	j;

	n_flag = 0;
	if (!g_data.cmd[g_data.y][1])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	j = 1;
	if (!(ft_strcmp(g_data.cmd[g_data.y][1], "-n")))
	{
		n_flag = 1;
		j++;
	}
	while (g_data.cmd[g_data.y][j])
	{
		ft_putstr_fd(g_data.cmd[g_data.y][j], 1);
		ft_putchar_fd(' ', 1);
		j++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_data.exit_status = 0;
}

void	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path));
	if (ret)
		printf("%s\n", g_data.pwd_dir_path);
	else
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		g_data.exit_status = 1;
		return ;
	}
	g_data.exit_status = 0;
}

/**
 * TODO: fix it to search for the environmental variable and replace it
 */
void	ft_env(void)
{
	int	x;
	int	k;
	char *v;
	int		i;
	int		j;
	char	**newenv;
	int		envsize;
	char	*var_name;
	char	*var;

	k = 1;
	while (g_data.cmd[g_data.y][k])
	{
		v = g_data.cmd[g_data.y][k];
		if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(g_data.cmd[g_data.y][k], 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putchar_fd('\n', 2);
			g_data.exit_status = 1;
			return ;
		}
		var_name = ft_substr(v, 0, ft_chrindex(v, '='));
		envsize = ft_strlen2(g_data.environ);
		newenv = (char **)malloc(sizeof(char **) * (envsize + 2));
		var = getenv(var_name);
		if (!var)
		{
			i = 0;
			while (g_data.environ[i])
			{
				newenv[i] = g_data.environ[i];
				i++;
			}
			newenv[i] = ft_strdup(v);
			i++;
			newenv[i] = NULL;
			g_data.environ = newenv;
		}
		else
		{
			i = 0;
			while (g_data.environ[i])
			{
				j = 0;
				while (var_name[j] == g_data.environ[i][j] && var_name && g_data.environ[i][j] != '=')
					j++;
				if (!var_name[j] && g_data.environ[i][j] == '=')
				{
					g_data.environ[i] = ft_strdup(v);
					break ;
				}
				i++;
			}
		}
		k++;
	}
	x = 0;
	while (g_data.environ[x])
	{
		printf("%s\n", g_data.environ[x]);
		x++;
	}
	g_data.exit_status = 0;
}
