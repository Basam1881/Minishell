/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:59:50 by bnaji             #+#    #+#             */
/*   Updated: 2021/10/03 14:17:52 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;
	char	*str1;
	size_t	i;

	str = (char *)dst;
	str1 = (char *)src;
	i = 0;
	if (str == 0 && str1 == 0)
		return (0);
	while (i < n)
	{
		str[i] = str1[i];
		i++;
	}
	return (dst);
}
