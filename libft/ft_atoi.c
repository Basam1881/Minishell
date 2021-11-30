/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:12:47 by bnaji             #+#    #+#             */
/*   Updated: 2021/10/08 01:10:23 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check(unsigned int nb, int mult)
{
	if (nb > 2147483647 && mult == 1)
		return (-1);
	else if (nb > 2147483648 && mult == -1)
		return (0);
	nb *= mult;
	return (nb);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					mult;
	unsigned long		nb;

	mult = 1;
	nb = 0;
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
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	nb = check(nb, mult);
	return (nb);
}
