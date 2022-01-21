/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wild_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:42:06 by mal-guna          #+#    #+#             */
/*   Updated: 2022/01/21 04:15:32 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_res_size(const char *str, char c, int index)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while(str[i])
	{
		while(str[i] && str[i] == c)
		{
			if(g_data.star_array[index] == -1)
			{
				break;
			}
			index++;
			i++;
		}
		if(str[i])
			size++;
		while(str[i])
		{
			if(str[i] == c && g_data.star_array[index] == 1)
			{
				break;
			}
			else if(str[i] == c && g_data.star_array[index] == -1)
			{
				index++;
			}
			i++;
		}
	}
	return (size);
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
		while (string[i] == ch)
		{
            if(g_data.star_array[index] == -1)
                break;
            i++;
			index++;
        }
        if (string[i] == '\0')
			break ;
		start = i;
		while (string[i] && !(string[i] == ch && g_data.star_array[index++] == 1))
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
	if (s == NULL)
	{
		res = (char **)malloc(sizeof(char *) * 1);
		res[0] = 0;
		return (res);
	}
	res = (char **)malloc(sizeof(char *) * (ft_res_size(s, c, index) + 1));
	if (!res)
		return (NULL);
	ft_fill_str(res, s, c, index);
	return (res);
}