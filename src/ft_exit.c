/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 08:48:02 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/31 14:40:26 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	shell_atoi(char *str)
{
	int						i;
	int						mult;
	int						nb_cnt;
	unsigned long long		nb;

	mult = 1;
	nb = 0;
	nb_cnt = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mult *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		if (mult == -1 && str[i] == '8' && nb == 922337203685477580
			&& !ft_isdigit(str[i + 1]))
		{
			nb = 0;
			i++;
			nb_cnt++;
			break ;
		}
		nb = (nb * 10) + (str[i] - '0');
		i++;
		nb_cnt++;
	}
	if (str[i] || (str[i - 1] == '+' || str[i - 1] == '-')
		|| nb_cnt > 19 || nb > LONG_MAX)
	{
		ft_putstr_fd("BnM bash: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_data.accepted_exit_flag = 1;
		return (255);
	}
	nb *= mult;
	return (nb);
}

void	ft_exit(void)
{
	int	n;

	ft_putendl_fd("exit", 1);
	if (!g_data.cmd[g_data.y][1])
	{
		printf("%s", NO_COLOR);
		exit_shell(g_data.exit_status);
	}
	else
	{
		n = shell_atoi(g_data.cmd[g_data.y][1]);
		if (!g_data.accepted_exit_flag && g_data.cmd[g_data.y][2])
		{
			ft_putendl_fd("BnM bash: exit: too many arguments", 2);
			g_data.exit_status = 1;
			return ;
		}
		g_data.accepted_exit_flag = 0;
		printf("%s", NO_COLOR);
		exit_shell(n);
	}
}
