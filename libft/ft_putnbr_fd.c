/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:57:27 by bnaji             #+#    #+#             */
/*   Updated: 2021/10/03 14:21:20 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int	new_nb;

	if (nb == 0)
		ft_putchar_fd(nb + 48, fd);
	else if (nb > 0)
	{
		new_nb = nb / 10;
		if (new_nb != 0)
			ft_putnbr_fd(new_nb, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		new_nb = 0 - (nb / 10);
		if (new_nb != 0)
			ft_putnbr_fd(new_nb, fd);
		ft_putchar_fd(0 - (nb % 10) + 48, fd);
	}
}
