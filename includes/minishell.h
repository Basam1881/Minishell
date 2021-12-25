/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:03:24 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/18 03:56:25 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * ------------------------------------------------------------------------------
 * |							Include Libraries								|
 * ------------------------------------------------------------------------------
 **/

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
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>

/**
 * ------------------------------------------------------------------------------
 * |							Define Variables								|
 * ------------------------------------------------------------------------------
 **/

# define PURPLE "\033[1;35m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define LIGHT_BLUE "\033[1;36m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BYELLOW  "\033[1;33m"
# define IYELLOW  "\033[3;33m"
# define NO_COLOR "\033[m"
# define MAC_PROMPT "\033[1;34m⚡⚡ BnM_Minishell\
\033[1;35m(\033[1;37m⌐■\033[1;35m_\033[1;37m■\033[1;35m)-\
-\033[1;33m︻╦╤─\033[m - -\033[1;32m> \033[1;37m"
# define LINUX_PROMPT " BnM_Minishell--$>"

/**
 * ------------------------------------------------------------------------------
 * |							Define Structures								|
 * ------------------------------------------------------------------------------
 **/

/**
 * sep_cmds: 2d array of commands in 
 * 		a cmdline that will be seperated by operators
 * no_env_arg_flag: flag that becomes one when 
 * 		there is no equivilent environment variable to replace with
 * dbl_op_f: flag for operators
 * 		that has two chars like (|| or && or << or >>)
 * n: counter for the number of commands. It can be used
 * 		in both (cmd) and (sep_cmds) like (cmd[data->n][][] or sep_cmds[data->n][])
 * ops_array: integer array that will store the operators
 * op_cnt: counter used for the operators array.
 * 		It's good cuz it's in the structure so no need to keep passing it
 **/
typedef struct s_data
{
	char	***cmd;
	char	*cmd_path;
	char	*cmdline;
	char	**sep_cmds;
	char	**env;
	int		split_flag;
	int		single_qoute_flag;
	int		double_qoute_flag;
	int		no_env_arg_flag;
	int		dbl_op_f;
	int		n;
	int		*ops_array;
	int		op_cnt;
	char	**environ;
	pid_t	c_pid;
	int		pid;
	int		pipes;
	int		pipe_flag;
	int		output_flag;
}				t_data;

/**
 * ------------------------------------------------------------------------------
 * |						Declare Global Variables							|
 * ------------------------------------------------------------------------------
 **/

t_data	g_data;

/**
 * ------------------------------------------------------------------------------
 * |							Functions Prototypes							|
 * ------------------------------------------------------------------------------
 **/
void	check_cmd(void);
char	**cmd_split(void);
void	failed_split(int n);
void	ft_exit(int n);
int		ft_chrindex(char *str, char c);
int		ft_strlen2(char **str);
void	ft_export(char *v);
void	ft_unset(char *v);
void	free_all(void);
void	initialize(void);
void	env_checker(int *x, int *i, int *j);
void	ultimate_3d_split(void);
void	operators_checker(int *x, int *ops_cnt, int flag);
void	ft_cd(void);
void	sig_handler(int signum, siginfo_t *info, void *ucontext);
void	execute_commands(int *i);
void	cmd_filter(int i);

#endif