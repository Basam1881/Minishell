/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:38:49 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 14:53:26 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_error(t_wild2 *wv, int *i)
{
	if (g_data.ops_array[*i - 1] == 2 || g_data.ops_array[*i - 1] \
	== 3 || g_data.ops_array[*i - 1] == 5)
	{
		if (wv->j == 0 && ft_strlen2(wv->expanded_array) > 1)
		{
			write (2, "Ambigous Redirect\n", 18);
			free_2d(&(wv->expanded_array));
			return (1);
		}
	}
	return (0);
}

/**
 * The is_resdir() function checks if the current operator in g_data.ops_array
 * is redirection or not. It returns 1 if it is and 0 if it's not.
**/
int	is_redir(int j)
{
	if (g_data.ops_array[j] == 2 || g_data.ops_array[j] == 3
		|| g_data.ops_array[j] == 5 || g_data.ops_array[j] == 6)
		return (1);
	return (0);
}

/* 
	This function will be called if there are more arguments
	other than file name ( only with redirections )
*/
void	ft_strjoin_2d(char *str2)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (ft_strlen2(g_data.cmd[g_data.y]) + 2));
	while (g_data.cmd[g_data.y][i])
	{
		res[i] = ft_strdup(g_data.cmd[g_data.y][i]);
		i++;
	}
	res[i++] = ft_strdup(str2);
	res[i] = NULL;
	i = 0;
	while (g_data.cmd[g_data.y][i])
		free(g_data.cmd[g_data.y][i++]);
	free(g_data.cmd[g_data.y]);
	g_data.cmd[g_data.y] = res;
}

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
