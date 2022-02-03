/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:15:01 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 16:01:55 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_cd_err(void)
{
	ft_putstr_fd("BnM bash: cd: ", 2);
	ft_putstr_fd(g_data.cmd[g_data.y][1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_data.exit_status = 1;
}

/**
 * TODO: add errors and make it for any n of commands
 */
void	ft_cd(void)
{
	int		i;
	char	*tmp;

	if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
		ft_putendl_fd(FAILURE_UPDATE_OLDPWD, 2);
	i = chdir(g_data.cmd[g_data.y][1]);
	if (!i)
	{
		tmp = ft_strjoin_moa("OLDPWD=", g_data.pwd_dir_path);
		ft_export(ft_strdup(tmp));
		free(tmp);
		if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
			ft_putendl_fd(FAILURE_UPDATE_PWD, 2);
		tmp = ft_strjoin_moa("PWD=", g_data.pwd_dir_path);
		ft_export(ft_strdup(tmp));
		free(tmp);
	}
	else if (i == -1)
	{
		print_cd_err();
		return ;
	}
	g_data.exit_status = 0;
}
