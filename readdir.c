/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:41:17 by mal-guna          #+#    #+#             */
/*   Updated: 2021/12/31 03:35:00 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "libft/libft.h"
#include <string.h>
//#include <strings2.h>

int	check_name(char *name, char *wild_card)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int name_index = 0;
	int wc_index = 0;
	int wc_number = 0;
	int wc_total = 0;
	int n = 0;
	char **res;
	char *temp;
	//printf("%s\n", name);
	res = ft_split(wild_card, '*');
	while(wild_card[k])
	{
		if(wild_card[k++] == '*')
			wc_total++;
	}
	if(wc_total == ft_strlen(wild_card))
		return (1);
	//printf("111\n");
	while(wild_card[wc_index])
	{
	//printf("222\n");
		
		while(wild_card [wc_index] == '*')
		{	
			wc_index++;
			wc_number ++;
		}
	//printf("2\n");

		if(!wild_card[wc_index])
			break;
		// maybe check here if we reach null;
		if(wc_number == 0)
		{
			temp = ft_strchr(ft_strdup(name), res[0][0]);
			if(!temp)
				return 0;
			//printf("|%s||%c|\n", name, res[0][0]);
			while(res[i][j])
			{
				//printf("hhhh\n");
				if(temp[j] != res[i][j])
					return 0;
				j++;
			}
			i++;
			name_index = j;
			//printf("3\n");
		}
		else if(wc_number == wc_total)
		{
			if((int) ft_strlen(name) - (int) ft_strlen(res[i]) < 0 || (int) ft_strlen(name) - (int) ft_strlen(res[i]) < name_index)
				return 0;
			temp = ft_strnstr(&name[ft_strlen(name) - ft_strlen(res[i])], res[i], ft_strlen(&name[ft_strlen(name) - ft_strlen(res[i])]));
			if(!temp)
				return 0;
		}
		else
		{
			temp = ft_strnstr(&name[name_index], res[i], ft_strlen(&name[name_index]));
			if(!temp)
				return (0);
			j = 0;
			while(res[i][j])
			{
				if (res[i][j] != temp[j])
					return 0;
				j++;
			}
			i++;
			name_index += j;
		}
		while(wild_card[wc_index] && wild_card[wc_index] != '*')
			wc_index++;
	}
	return 1;
}

int main(int ac, char **av)
{
	DIR *d;
	struct dirent *dir_struct;

	d = opendir(".");
	if (!d)
		return (1);
	while(1)
	{
		dir_struct = readdir(d);
		if(!dir_struct)
			break;
		//check_name(dir_struct->d_name, av[1]);
		//printf("~%s~  ~%s~\n", dir_struct->d_name, av[1]);
		if(check_name(dir_struct->d_name, av[1]))
			printf("%s\n", dir_struct->d_name);
		//printf("|%s|\n", dir_struct->d_name);
	}
	closedir(d);
}

