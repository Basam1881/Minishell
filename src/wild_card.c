/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 09:42:06 by mal-guna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/31 21:01:01 by bnaji            ###   ########.fr       */
=======
/*   Updated: 2022/01/25 22:00:02 by mal-guna         ###   ########.fr       */
>>>>>>> 033abde292f8e8c46e3bfaa8e8f6c4647a115b13
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	free_2d(char ***str)
{
	int i = 0;
	if(*str)
	{
		while((*str)[i])
			free((*str)[i++]);
		free(*str);	
		*str = NULL;
	}
}
int	check_name(char *name, char *wild_card)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int name_index = 0;
	int wc_index = 0;
	int wc_number = 0;
	int wc_total = 0;
	//int n = 0;
	char **res;
	char *temp;
	int temp_index;

	temp_index = g_data.star_array_index;
	res = ft_wild_split(wild_card, '*',g_data.star_array_index);
	while(wild_card[k])
	{
		if(wild_card[k++] == '*' && g_data.star_array[temp_index++] == 1)
			wc_total++;
		
	}
	if(wc_total == (int) ft_strlen(wild_card))
	{
		free_2d(&res);
		return (1);
	}
	while(wild_card[wc_index])
	{
		while(wild_card[wc_index] == '*')
		{
			if(g_data.star_array[g_data.star_array_index] == -1)
				break;
			wc_index++;
			wc_number ++;
			g_data.star_array_index++;
		}
		if(!wild_card[wc_index])
			break;
		if(wc_number == 0)
		{
			temp = ft_strchr(name, res[0][0]);
			if(!temp || ft_strlen(temp) != ft_strlen(name))
			{
				free_2d(&res);
				return (0);
			}
			while(res[i][j])
			{
				if(temp[j] != res[i][j])
				{
					free_2d(&res);
					return (0);
				}
				j++;
			}
			i++;
			name_index = j;
		}
		else if(wc_number == wc_total)
		{
			if((int) ft_strlen(name) - (int) ft_strlen(res[i]) < 0 || (int) ft_strlen(name) - (int) ft_strlen(res[i]) < name_index)
				{
					free_2d(&res);
					return (0);
				}
			temp = ft_strnstr(&name[ft_strlen(name) - ft_strlen(res[i])], res[i], ft_strlen(&name[ft_strlen(name) - ft_strlen(res[i])]));
			if(!temp)
				{
					free_2d(&res);
					return (0);
				}
		}
		else
		{
			temp = ft_strnstr(&name[name_index], res[i], ft_strlen(&name[name_index]));
			if(!temp)
				{
					free_2d(&res);
					return (0);
				}
			j = 0;
			while(res[i][j])
			{
				if (res[i][j] != temp[j])
				{
					free_2d(&res);
					return (0);
				}
				j++;
			}
			i++;
			name_index = -(name - temp) + j;
		}
		while(wild_card[wc_index])
		{
			if(wild_card[wc_index] == '*' && g_data.star_array[g_data.star_array_index] == 1)
			{
				break;
			}
			else if(wild_card[wc_index] == '*' && g_data.star_array[g_data.star_array_index] == -1)
			{
				g_data.star_array_index++;
			}
			wc_index++;
		}
	}
	free_2d(&res);
	return 1;
}

int	count_wild_card(char *wild_card)
{
	DIR *d;
	struct dirent *dir_struct;
	int count;

	count = 0;
	d = opendir(".");
	if (!d)
		return (-1);
	while(1)
	{
		dir_struct = readdir(d);
		if(!dir_struct)
			break;
		if(dir_struct->d_name[0] == '.')
			continue;
		g_data.star_array_index = g_data.star_index_temp;
		if(check_name(dir_struct->d_name, wild_card))
			count ++;
	}
	closedir(d);
	return count;
}

char	**expand_wild_card(char *wild_card)
{
	DIR *d;
	struct dirent *dir_struct;
	int size;
	int i;
	char **res;

	i = 0;
	size = count_wild_card(wild_card);
	if(size > 0)
		res = malloc(sizeof(char**) * (size + 1));
	else
		return (NULL);
	d = opendir(".");
	if (!d)
		return (NULL);
	while(1)
	{
		dir_struct = readdir(d);
		if(!dir_struct)
			break;
		if(dir_struct->d_name[0] == '.')
			continue;
		g_data.star_array_index = g_data.star_index_temp;
		if(check_name(dir_struct->d_name, wild_card))
			res[i++] = ft_strdup(dir_struct->d_name);
	}
	res[i] = NULL;
	closedir(d);
	return (res);
}
void	insert_array(char **expandded_array, int i, int *j)
{
	char **res;
	int k;
	int n;
	int temp;

	k = 0;
	n = 0;
	res = malloc(sizeof(char *) * (ft_strlen2(g_data.cmd[i]) + ft_strlen2(expandded_array) + 1));
	while(k < *j)
	{
		res[k] = ft_strdup(g_data.cmd[i][k]);
		k++;
	}
	while(expandded_array[n])
		res[k++] = ft_strdup(expandded_array[n++]);
	temp = k - 1;
	(*j)++;
	while(g_data.cmd[i][(*j)])
	{
		res[k++] = ft_strdup(g_data.cmd[i][*j]);
		(*j)++;
	}
	res[k] = NULL;
	k = 0;
	*j = temp;
	while (g_data.cmd[i][k])
		free(g_data.cmd[i][k++]);
	free(g_data.cmd[i][k]);
	free(g_data.cmd[i]);
	g_data.cmd[i] = res;
}

int	handle_wild_card(int i)
{
	int j;
	int k;
	int wc_flag;
	char **expanded_array;
	
	j = 0;
	while(g_data.cmd[i][j])
	{
		k = 0;
		wc_flag = 0;
		if(ft_strchr(g_data.cmd[i][j], '*'))
		{
			expanded_array = expand_wild_card(g_data.cmd[i][j]);
			while(g_data.cmd[i][j][k])
			{
				if(g_data.cmd[i][j][k] == '*')
				{
					if(g_data.star_array[g_data.star_index_temp] == 1)
						wc_flag = 1;
					g_data.star_index_temp++;
				}
				k++;
			}
			if(!wc_flag)
			{
				if(g_data.cmd[i][j])
					j++;
				free_2d(&expanded_array);
				continue;
			}
			if(expanded_array)
			{
				if(i > 0)
				{
					if(g_data.ops_array[i-1] == 2 || g_data.ops_array[i-1] == 3 || g_data.ops_array[i-1] == 5)
					{
						if(j == 0 && ft_strlen2(expanded_array)  > 1)
						{
						write(2, "Ambigous Redirect\n", 18);
						free_2d(&expanded_array);
						return (-1);	
						}
					}
				}
				insert_array(expanded_array, i, &j);
				free_2d(&expanded_array);
			}
		}
		if(g_data.cmd[i][j])
			j++;
	}
	return (0);
}