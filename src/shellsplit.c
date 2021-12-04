/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:19:25 by dfurneau          #+#    #+#             */
/*   Updated: 2021/12/04 16:29:59 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	fill_strings(char **str, char *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		x;

// 	i = 0;
// 	x = 0;
// 	while (s[x])
// 	{
// 		if (s[x] == c)
// 			x++;
// 		else
// 		{
// 			j = 0;
// 			while (s[x] && s[x] != c)
// 			{
// 				str[i][j] = s[x];
// 				j++;
// 				x++;
// 			}
// 			str[i][j] = 0;
// 			i++;
// 		}
// 	}
// 	str[i] = 0;
// }

// static void	ft_free(char **str, int n)
// {
// 	while (n >= 0)
// 	{
// 		if (str[n] != NULL)
// 			free(str[n]);
// 		n--;
// 	}
// 	free(str);
// }

// static int	allocte_strings(char **str, char *s, char c)
// {
// 	int		i;
// 	int		size;
// 	int		x;

// 	i = 0;
// 	x = 0;
// 	while (s[x])
// 	{
// 		if (s[x] == c)
// 			x++;
// 		else
// 		{
// 			size = 0;
// 			while (s[x] && s[x++] != c)
// 				size++;
// 			str[i] = (char *)malloc(sizeof(char) * size + 1);
// 			if (!str[i])
// 			{
// 				ft_free(str, i);
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// 	return (1);
// }

static int	word_counter(char *s)
{
	int		i;
	int		words;
	int		single_qoute;
	int		double_qoute;

	i = 0;
	words = 0;
	single_qoute = 0;
	double_qoute = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
		{
			if (s[i] == '\'')
			{
				i++;
				single_qoute = 1;
			}
			else if (s[i] == '"')
			{
				i++;
				double_qoute = 1;
			}
			if ((s[i] == '\'' && single_qoute) || (s[i] == '"' && double_qoute))
			{
				if (s[i] == '\'')
						single_qoute = 0;
					else
						double_qoute = 0;
				i++;
			}
			else
			{
				printf("c = %c\n", s[i]);
				words++;
			}
			while (s[i] && (s[i] != ' ' || (s[i] == ' ' && (single_qoute || double_qoute))))
			{
				if ((s[i] == '\'' && single_qoute) || (s[i] == '"' && double_qoute))
				{
					if (s[i] == '\'')
						single_qoute = 0;
					else
						double_qoute = 0;
				}
				i++;
			}
		}
	}
	printf("words = %d\n", words);
	exit (0);
	return (words);
}

char	**shell_split(char *cmdline)
{
	char	**str;
	int		words;

	if (!cmdline)
		return (ft_calloc(1, 1));
	words = word_counter((char *)cmdline);
	str = (char **)malloc(sizeof(char *) * words + 1);
	if (!(str))
		return (0);
	// allocte_strings(str, (char *)cmdline);
	// fill_strings(str, (char *)cmdline);
	return (str);
}

int main()
{
	char **av = shell_split("echo \"h\" \"sss\"ff    \"\" \" \"  i ev");
	return (0);
}