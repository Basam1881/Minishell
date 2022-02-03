/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:24:53 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 15:25:25 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path));
	if (ret)
		printf("%s\n", g_data.pwd_dir_path);
	else
	{
		ft_putstr_fd("BnM bash: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_data.exit_status = 1;
		return ;
	}
	g_data.exit_status = 0;
}
