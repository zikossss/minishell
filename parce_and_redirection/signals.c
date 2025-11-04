/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:47:38 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/14 02:48:21 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int signum)
{
	g_var_for_signal = signum;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	recievesignals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handler1(int signum)
{
	g_var_for_signal = signum;
	write(1, "^C", 3);
	close(STDIN_FILENO);
}

void	heredoc_signal(void)
{
	signal(SIGINT, handler1);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_sihandler(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
