/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:42:06 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 14:55:55 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_stars(char *wild_card)
{
	while (wild_card[g_data.wv->wc_index] == '*')
	{
		if (g_data.star_array[g_data.star_array_index] == -1)
			break ;
		g_data.wv->wc_index++;
		g_data.wv->wc_number ++;
		g_data.star_array_index++;
	}
	if (!wild_card[g_data.wv->wc_index])
		return (1);
	return (0);
}

int	count_wild_card(char *wild_card)
{
	DIR				*d;
	struct dirent	*dir_struct;
	int				count;

	count = 0;
	d = opendir(".");
	if (!d)
		return (-1);
	while (1)
	{
		dir_struct = readdir(d);
		if (!dir_struct)
			break ;
		if (dir_struct->d_name[0] == '.')
			continue ;
		g_data.star_array_index = g_data.star_index_temp;
		if (check_name(dir_struct->d_name, wild_card))
			count++;
	}
	closedir(d);
	return (count);
}

void	insert_array(char **expandded_array, int i, int *j)
{
	char	**res;
	int		k;
	int		n;
	int		temp;

	k = -1;
	n = 0;
	res = malloc(sizeof(char *) * (ft_strlen2(g_data.cmd[i]) + \
	 ft_strlen2(expandded_array) + 1));
	while (++k < *j)
		res[k] = ft_strdup(g_data.cmd[i][k]);
	while (expandded_array[n])
		res[k++] = ft_strdup(expandded_array[n++]);
	temp = k - 1;
	(*j)++;
	while (g_data.cmd[i][(*j)])
	{
		res[k++] = ft_strdup(g_data.cmd[i][*j]);
		(*j)++;
	}
	res[k] = NULL;
	k = 0;
	*j = temp;
	free_2d(&g_data.cmd[i]);
	g_data.cmd[i] = res;
}

int	is_wc(t_wild2 *wv, int *i)
{
	wv->expanded_array = expand_wild_card(g_data.cmd[*i][wv->j]);
	while (g_data.cmd[*i][wv->j][wv->k])
	{
		if (g_data.cmd[*i][wv->j][wv->k] == '*')
		{
			if (g_data.star_array[g_data.star_index_temp] == 1)
				wv->wc_flag = 1;
			g_data.star_index_temp++;
		}
		wv->k++;
	}
	if (!(wv->wc_flag))
	{
		if (g_data.cmd[*i][wv->j])
			wv->j++;
		free_2d(&(wv->expanded_array));
		return (1);
	}
	return (0);
}

int	handle_wild_card(int i)
{
	t_wild2	wv;

	wv.j = 0;
	while (g_data.cmd[i][wv.j])
	{
		wv.k = 0;
		wv.wc_flag = 0;
		if (ft_strchr(g_data.cmd[i][wv.j], '*'))
		{
			if (is_wc(&wv, &i))
				continue ;
			if (wv.expanded_array)
			{
				if (i > 0)
					if (check_for_error(&wv, &i))
						return (-1);
				insert_array(wv.expanded_array, i, &(wv.j));
				free_2d(&(wv.expanded_array));
			}
		}
		if (g_data.cmd[i][wv.j])
			wv.j++;
	}
	return (0);
}
