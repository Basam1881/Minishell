/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wild_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:42:06 by mal-guna          #+#    #+#             */
/*   Updated: 2022/02/02 11:10:37 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	ft_res_size(const char *str, char c, int index, int *size)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return ;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			if (g_data.star_array[index] == -1)
				break ;
			index++;
			i++;
		}
		if (str[i])
			(*size)++;
		while (str[i])
		{
			if (str[i] == c && g_data.star_array[index] == 1)
				break ;
			else if (str[i] == c && g_data.star_array[index] == -1)
				index++;
			i++;
		}
	}
}

void	check_if_wild(int *i, int *index, char const *string, char ch)
{
	while (string[*i] == ch)
	{
		if (g_data.star_array[*index] == -1)
			break ;
		(*i)++;
		(*index)++;
	}
}

static	void	ft_fill_str(char **res, char const *string, char ch, int index)
{
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (string[i])
	{
		check_if_wild(&i, &index, string, ch);
		if (string[i] == '\0')
			break ;
		start = i;
		while (string[i] && !(string[i] == ch \
		&& g_data.star_array[index++] == 1))
			i++;
		index--;
		end = i;
		res[j] = ft_substr(string, start, end - start);
		j++;
	}
	res[j] = 0;
}

char	**ft_wild_split(char const *s, char c, int index)
{
	char	**res;
	int		size;

	size = 0;
	ft_res_size(s, c, index, &size);
	if (s == NULL)
	{
		res = (char **)malloc(sizeof(char *) * 1);
		res[0] = 0;
		return (res);
	}
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	ft_fill_str(res, s, c, index);
	return (res);
}
