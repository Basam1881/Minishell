/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:03:24 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/06 16:32:03 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define PURPLE "\033[1;35m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define LIGHT_BLUE "\033[1;36m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BYELLOW  "\033[1;33m"
# define IYELLOW  "\033[3;33m"
# define NO_COLOR "\033[m"

typedef struct s_data
{
	char	**cmd;
	char	*cmdline;
	int		split_flag;
	int		single_qoute_flag;
	int		double_qoute_flag;
}				t_data;
extern char	**environ;
void	check_cmd(t_data *data);
char	**cmd_split(t_data *data);
void	failed_split(t_data *data, int n);
void	error(t_data *data, int n);

#endif