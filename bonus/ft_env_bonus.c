/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:28:49 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 14:29:27 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: fix it to search for the environmental variable and replace it
 */
void	ft_env(void)
{
	int		x;
	int		k;
	char	*v;

	k = 1;
	while (g_data.cmd[g_data.y][k])
	{
		v = ft_strdup(g_data.cmd[g_data.y][k]);
		if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(g_data.cmd[g_data.y][k], 2);
			ft_putendl_fd(": No such file or directory", 2);
			ft_putchar_fd('\n', 2);
			g_data.exit_status = 1;
			free(v);
			return ;
		}
		ft_export(v);
		k++;
	}
	x = 0;
	while (g_data.environ[x])
		printf("%s\n", g_data.environ[x++]);
	g_data.exit_status = 0;
}
