/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:17:55 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/18 00:50:20 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * struct termios saved;

void restore(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}
**/
/**
 *  struct termios attributes;
    tcgetattr(STDIN_FILENO, &saved);
    atexit(restore);
    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
 **/

void	sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void) signum;
	(void) info;
	(void) ucontext;
	// kill(g_data.c_pid, SIGKILL);
	// if (g_data.c_pid == 0)
	// {
		// printf("hi from child: %d\n", g_data.c_pid);
		// printf("Hi child\n"); 
		// rl_replace_line("", 0);
		// write(0, "\n", 1);
		// rl_on_new_line();
		// rl_redisplay();
	// 	exit (0);
	// }
	// else
	// {
		// printf("Hi parent\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	write(0, "\n", 1);
	rl_redisplay();
	// }
}
