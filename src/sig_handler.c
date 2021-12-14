/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:17:55 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/14 11:34:09 by bnaji            ###   ########.fr       */
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
	write(0, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
