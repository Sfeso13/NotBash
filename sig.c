/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:02:16 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/22 15:03:35 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

pid_t	child_pid(int value, int setorget)
{
	static pid_t	pid;

	if (setorget == 1)
		pid = value;
	else
		return (pid);
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (!(waitpid(-1, NULL, WNOHANG)))
		return ;
	g_signal_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
