/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:38:41 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 17:45:01 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name(char *name, char *wild_card)
{
	g_data.wv = malloc(sizeof(struct s_wild) + 1);
	if (setup_wild_card(wild_card))
		return (1);
	while (wild_card[g_data.wv->wc_index])
	{
		if (count_stars(wild_card))
			break ;
		if (g_data.wv->wc_number == 0)
		{
			if (wild_on_start(name))
				return (0);
		}
		else if (g_data.wv->wc_number == g_data.wv->wc_total)
		{
			if (wild_on_end(name))
				return (0);
		}
		else
			if (wild_on_mid(name))
				return (0);
		next_wild_part(wild_card);
	}
	free_2d(&(g_data.wv->res));
	free(g_data.wv);
	return (1);
}

int	setup_dv(t_dir *dv, char *wild_card)
{
	dv->i = 0;
	dv->size = count_wild_card(wild_card);
	if (dv->size > 0)
		dv->res = malloc(sizeof(char **) * (dv->size + 1));
	else
		return (1);
	return (0);
}

int	setup_wild_card(char *wild_card)
{
	set_wild_variables(wild_card);
	while (wild_card[g_data.wv->k])
		if (wild_card[g_data.wv->k++] == '*' && \
		g_data.star_array[g_data.wv->temp_index++] == 1)
			g_data.wv->wc_total++;
	if (g_data.wv->wc_total == (int) ft_strlen(wild_card))
	{
		free_2d(&(g_data.wv->res));
		free(g_data.wv);
		return (1);
	}
	return (0);
}

void	set_wild_variables(char *wild_card)
{
	g_data.wv->i = 0;
	g_data.wv->j = 0;
	g_data.wv->k = 0;
	g_data.wv->name_index = 0;
	g_data.wv->wc_index = 0;
	g_data.wv->wc_number = 0;
	g_data.wv->wc_total = 0;
	g_data.wv->res = \
	ft_wild_split(wild_card, '*', g_data.star_array_index);
	g_data.wv->temp = 0;
	g_data.wv->temp_index = g_data.star_array_index;
}

void	free_2d(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
			free((*str)[i++]);
		free(*str);
		*str = NULL;
	}
}
