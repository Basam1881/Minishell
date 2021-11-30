/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:35:20 by bnaji             #+#    #+#             */
/*   Updated: 2021/10/08 13:27:26 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*y;

	if (!del)
		return ;
	x = *lst;
	while (x)
	{
		y = x;
		x = x->next;
		del(y->content);
		free(y);
	}
	*lst = NULL;
}
