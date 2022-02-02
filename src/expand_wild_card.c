/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_card.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:39:02 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 14:39:58 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wild_on_start(char *name)
{
	g_data.wv->temp = ft_strchr(name, g_data.wv->res[0][0]);
	if (!(g_data.wv->temp) || ft_strlen(g_data.wv->temp) != ft_strlen(name))
	{
		free_2d(&(g_data.wv->res));
		return (1);
	}
	while (g_data.wv->res[g_data.wv->i][g_data.wv->j])
	{
		if (g_data.wv->temp[g_data.wv->j] != \
		g_data.wv->res[g_data.wv->i][g_data.wv->j])
		{
			free_2d(&(g_data.wv->res));
			return (1);
		}
		g_data.wv->j++;
	}
	g_data.wv->i++;
	g_data.wv->name_index = g_data.wv->j;
	return (0);
}

int	wild_on_mid(char *name)
{
	g_data.wv->temp = ft_strnstr(&name[g_data.wv->name_index], \
	g_data.wv->res[g_data.wv->i], \
	ft_strlen(&name[g_data.wv->name_index]));
	if (!(g_data.wv->temp))
	{
		free_2d(&(g_data.wv->res));
		return (1);
	}
	g_data.wv->j = 0;
	while (g_data.wv->res[g_data.wv->i][g_data.wv->j])
	{
		if (g_data.wv->res[g_data.wv->i][g_data.wv->j] \
		!= g_data.wv->temp[g_data.wv->j])
		{
			free_2d(&(g_data.wv->res));
			return (1);
		}
		g_data.wv->j++;
	}
	g_data.wv->i++;
	g_data.wv->name_index = -(name - g_data.wv->temp) + g_data.wv->j;
	return (0);
}

int	wild_on_end(char *name)
{
	if ((int) ft_strlen(name) - \
	(int) ft_strlen(g_data.wv->res[g_data.wv->i]) < 0 \
	|| ((int) ft_strlen(name) - (int) ft_strlen(g_data.wv->res[g_data.wv->i]) \
	 < g_data.wv->name_index))
	{
		free_2d(&(g_data.wv->res));
		return (1);
	}
	g_data.wv->temp = ft_strnstr(&name[ft_strlen(name) - \
	ft_strlen(g_data.wv->res[g_data.wv->i])], \
	g_data.wv->res[g_data.wv->i], ft_strlen(&name[ft_strlen(name) \
	 - ft_strlen(g_data.wv->res[g_data.wv->i])]));
	if (!g_data.wv->temp)
	{
		free_2d(&(g_data.wv->res));
		return (1);
	}
	return (0);
}

void	next_wild_part(char *wild_card)
{
	while (wild_card[g_data.wv->wc_index])
	{
		if (wild_card[g_data.wv->wc_index] == '*' \
		&& g_data.star_array[g_data.star_array_index] == 1)
		{
			break ;
		}
		else if (wild_card[g_data.wv->wc_index] == '*' \
		&& g_data.star_array[g_data.star_array_index] == -1)
		{
			g_data.star_array_index++;
		}
		g_data.wv->wc_index++;
	}
}

char	**expand_wild_card(char *wild_card)
{
	t_dir	dv;

	if (setup_dv(&dv, wild_card))
		return (NULL);
	dv.d = opendir(".");
	if (!(dv.d))
		return (NULL);
	while (1)
	{
		dv.dir_struct = readdir(dv.d);
		if (!(dv.dir_struct))
			break ;
		if (dv.dir_struct->d_name[0] == '.')
			continue ;
		g_data.star_array_index = g_data.star_index_temp;
		if (check_name(dv.dir_struct->d_name, wild_card))
			dv.res[dv.i++] = ft_strdup(dv.dir_struct->d_name);
	}
	dv.res[dv.i] = NULL;
	closedir(dv.d);
	return (dv.res);
}
