/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_q_and_star_arrays.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:23:12 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 19:25:07 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_dollar_q_flag(int x)
{
	if ((g_data.single_qoute_flag && (g_data.cmdline[x + 1] == '?'
				|| (g_data.cmdline[x + 1] == '\'' && g_data
					.cmdline[x + 2] == '?'))) || (g_data
			.double_qoute_flag && g_data.cmdline[x + 1]
			== '"' && g_data.cmdline[x + 2] == '?'))
		g_data.q_array[g_data.question_cnt++] = -1;
	else if ((!g_data.single_qoute_flag && !g_data
			.double_qoute_flag && g_data.cmdline[x + 1] == '?')
		|| (g_data.double_qoute_flag && g_data.cmdline[x + 1] == '?'))
		g_data.q_array[g_data.question_cnt++] = 1;
}

/**
 * The q_and_star_assigner() function allocates and
 * assign an array of flags for the wildcard (*)
**/
void	q_and_star_assigner(int x, int flag)
{
	if (!flag)
	{
		if (g_data.cmdline[x] == '*')
			g_data.star_cnt++;
		else if (g_data.cmdline[x] == '$' && g_data.cmdline[x + 1] == '?')
			g_data.question_cnt++;
	}
	else
	{
		if (g_data.cmdline[x] == '*')
		{
			if (g_data.single_qoute_flag || g_data.double_qoute_flag)
				g_data.star_array[g_data.star_cnt++] = -1;
			else
				g_data.star_array[g_data.star_cnt++] = 1;
		}
		else if (g_data.cmdline[x] == '$')
			set_dollar_q_flag(x);
	}
}
