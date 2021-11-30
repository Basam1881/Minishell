/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:41:32 by bnaji             #+#    #+#             */
/*   Updated: 2021/11/06 16:17:42 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*is_positive(long n, char *str)
{
	int		nb;
	int		count;

	nb = n;
	count = count_digits(nb);
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (0);
	str[count] = 0;
	nb = n;
	while (count-- > 0)
	{
		nb = n % 10;
		n = n / 10;
		str[count] = nb + 48;
	}
	return (str);
}

static char	*is_negative(long n, char *str)
{
	int	nb;
	int	count;

	n = n * -1;
	nb = n;
	count = count_digits(nb);
	str = (char *)malloc(sizeof(char) * count + 2);
	if (!str)
		return (0);
	str[count + 1] = 0;
	while (count > 0)
	{
		nb = n % 10;
		n = n / 10;
		str[count] = nb + 48;
		count--;
	}
	str[count] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;

	str = 0;
	num = (long)n;
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) + 1);
		if (!str)
			return (0);
		str[0] = '0';
		str[1] = 0;
	}
	else if (n > 0)
		str = is_positive(num, str);
	else
		str = is_negative(num, str);
	return (str);
}
