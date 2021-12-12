/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:03:24 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/11 15:08:22 by bnaji            ###   ########.fr       */
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
# include <fcntl.h>

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
	char	***cmd;
	char	*cmdline;
	char	**sep_cmds;/*This is a 2d array of commands in a cmdline that will be seperated by operators*/
	char	**env;
	int		split_flag;
	int		single_qoute_flag;
	int		double_qoute_flag;
	int		no_env_arg_flag;/*This is a flag that becomes one when there is no equivilent environment variable to replace with*/
	int		dbl_op_f;/*This is a flag for operators that has two chars like (|| or && or << or >>)*/
	int		n;/*This is a counter for the number of commands. It can be used in both (cmd) and (sep_cmds) like (cmd[data->n][][] or sep_cmds[data->n][])*/
	int		*ops_array;/*This the integer array that will store the operators*/
	int		op_cnt;/*This is counter used for the operators array. It's good cuz it's in the structure so no need to keep passing it*/
}				t_data;
extern char	**environ;
void	check_cmd(t_data *data);
char	**cmd_split(t_data *data);
void	failed_split(t_data *data, int n);
void	ft_exit(t_data *data, int n);
int		ft_chrindex(char *str, char c);
int		ft_strlen2(char **str);
void	ft_export(char *v);
void	ft_unset(char *v);
void	free_all(t_data *data);
void	initialize(t_data *data);
void	env_checker(t_data *data, int *x, int *i, int *j);
void	ultimate_3d_split(t_data *data);
void	operators_checker(t_data *data, int *x, int *ops_cnt, int flag);
void	execute_commands(t_data *data, int *i);
#endif