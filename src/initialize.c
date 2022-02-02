/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:46:43 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/02 10:03:21 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	reset();
}

static void	reset_other_ints(void)
{
	g_data.dbl_op_f = 0;
	g_data.digit_env = 0;
	g_data.n = 0;
	g_data.op_cnt = 0;
	g_data.last_op = 0;
	g_data.parentheses_cnt = 0;
	g_data.star_cnt = 0;
	g_data.question_cnt = 0;
	g_data.closing_parenthese = 0;
	g_data.c_pid = 0;
	g_data.sub_pid = 0;
	g_data.was_child = 0;
	g_data.pipes = -1;
	g_data.star_array_index = 0;
	g_data.star_index_temp = 0;
	g_data.wait_n = 0;
	g_data.error_flag = 0;
}

static void	reset_strs(void)
{
	g_data.cmdline = NULL;
	g_data.cmd = NULL;
	g_data.sep_cmds = NULL;
	g_data.ops_array = NULL;
	g_data.star_array = NULL;
	g_data.q_array = NULL;
	g_data.cmd_path = NULL;
}

static void	reset_flags(void)
{
	g_data.no_env_arg_flag = 0;
	g_data.accepted_exit_flag = 0;
	g_data.double_qoute_flag = 0;
	g_data.single_qoute_flag = 0;
	g_data.is_path_flag = 0;
	g_data.empty_flag = 0;
	g_data.under_process_flag = 0;
	g_data.sub_exit_flag = 0;
	g_data.inside_parentheses_flag = 0;
	g_data.pipe_flag = 0;
	g_data.output_flag = 0;
	g_data.input_flag = 0;
	g_data.pipe_child_flag = 0;
	g_data.cmd_flag = 1;
}

void	reset(void)
{
	reset_strs();
	reset_flags();
	reset_other_ints();
	g_data.fdout = dup(STDOUT_FILENO);
	g_data.fdin = dup(STDIN_FILENO);
	dup2(g_data.fdin, STDIN_FILENO);
	dup2(g_data.fdout, STDOUT_FILENO);
}
