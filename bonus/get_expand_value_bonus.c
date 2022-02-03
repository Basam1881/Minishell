/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expand_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:25:00 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 16:25:31 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_expnd_val(char *var_name)
{
	int		i;
	char	*temp;
	char	*val;

	i = 0;
	while (g_data.environ[i])
	{
		temp = ft_substr(g_data.environ[i], 0,
				ft_chrindex(g_data.environ[i], '='));
		if (!ft_strcmp(var_name, temp))
		{
			val = ft_strdup(ft_strchr(g_data.environ[i], '=') + 1);
			free(temp);
			return (val);
		}
		free(temp);
		i++;
	}
	return (NULL);
}
