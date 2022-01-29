/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:46:43 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/23 13:48:08 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(void)
{
	// struct sigaction	sig_sig;

	// g_data.exit_status = 0;
	// g_data.c_exit_flag = 0;
	// sig_sig.sa_flags = 0;
	// sig_sig.sa_mask = 0;
	// sig_sig.sa_sigaction = &sig_handler;
	// sigaction(SIGINT, &sig_sig, NULL);
	// sigaction(SIGQUIT, &sig_sig, NULL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	reset(void)
{
	g_data.cmdline = NULL;
	g_data.cmd = NULL;
	g_data.sep_cmds = NULL;
	g_data.ops_array = NULL;
	g_data.star_array = NULL;
	g_data.cmd_path = NULL;
	g_data.no_env_arg_flag = 0;
	g_data.accepted_exit_flag = 0;
	g_data.double_qoute_flag = 0;
	g_data.single_qoute_flag = 0;
	g_data.dbl_op_f = 0;
	g_data.digit_env = 0;
	g_data.n = 0;
	g_data.op_cnt = 0;
	g_data.last_op = 0;
	g_data.parentheses_cnt = 0;
	g_data.star_cnt = 0;
	g_data.empty_flag = 0;
	g_data.under_process_flag = 0;
	g_data.closing_parenthese = 0;
	g_data.c_pid = 0;
	g_data.sub_pid = 0;
	g_data.sub_exit_flag = 0;
	g_data.inside_parentheses_flag = 0;
	g_data.was_child = 0;
	g_data.pipes = -1;
	g_data.pipe_flag = 0;
	g_data.output_flag = 0;
	g_data.input_flag = 0;
	g_data.star_array_index = 0;
	g_data.star_index_temp = 0;
	g_data.fdout = dup(STDOUT_FILENO);
	g_data.fdin = dup(STDIN_FILENO);
}
