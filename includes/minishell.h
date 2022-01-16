/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:03:24 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/16 19:18:39 by bnaji            ###   ########.fr       */
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
# include "../gnl/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>

/**
 * ------------------------------------------------------------------------------
 * |							Define Variables								|
 * ------------------------------------------------------------------------------
 **/

# define CLEAR_SCREEN "\033[?1049h\033[H"
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
# define FIRST_PARENTH_MSG "BNM bash: syntax error near unexpected token `)'"
# define NEWLINE_MSG "BNM bash: syntax error near unexpected token `newline'"
# define UNCLOSED_SINGLE "BNM bash: syntax error (unclosed single qoutes)"
# define UNCLOSED_DOUBLE "BNM bash: syntax error (unclosed double qoutes)"
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
	int		*star_array;
	int		op_cnt;
	char	**environ;
	pid_t	c_pid;
	pid_t	sub_pid;
	int		sub_status;
	int		sub_exit_flag;
	int		inside_parentheses_flag;
	int		was_child;
	int		closing_parenthese;
	int		pid;
	int		exit_status;
	int		c_exit_flag;
	int		empty_flag;
	int		pipes;
	int		pipe_flag;
	int		is_pipe;
	int		is_dbl_pipe;
	int		is_dbl_and;
	int		output_flag;
	int		input_flag;
	int		under_process_flag;
	int		last_op;
	int		parentheses_cnt;
	int		star_cnt;
	int		x;
	int		y;
	int		x_holder;
	int		y_holder;
	int		fdout;
	int		fdin;
	char	**test_str; // this is just temp to test ft_strjoin_2d
	char	pwd_dir_path[1000];
	int		fd[][2];
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
void	failed_sep_cmds(int n);
void	exit_shell(int n);
int		ft_chrindex(char *str, char c);
int		ft_strlen2(char **str);
void	ft_export(char *v);
void	ft_unset(char *v);
void	free_all(void);
void	reset(void);
void	init(void);
void	env_checker(int *x, int *i, int *j);
int		ultimate_3d_split(void);
int		operators_checker(int *x, int *ops_cnt, int flag);
void	ft_cd(void);
void	ft_echo(void);
void	ft_pwd(void);
void	ft_env(void);
void	sig_handler(int signum);
void	execute_commands(int i);
void	cmd_filter(int i);
void	save_exit_status(void);
void	ft_exit(void);
void	env_exit(int *x, int *i, int *j);
int		empty_cmd_checker(void);
void	error_printer(void);
void	dbl_ops_handler(void);
int		unexpected_msg(int x, int flag, char *s);

#endif