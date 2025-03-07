/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/07 00:24:54 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_status(t_env **env, int status, pid_t cpid)
{
	char	*stat;

	stat = NULL;
	if (cpid == child_pid(0, 0))
	{
		if (g_signal_received == 1)
			g_signal_received = 0;
		if (WIFSIGNALED(status))
			stat = ft_itoa(WTERMSIG(status) + 128);
		else if (WIFEXITED(status))
			stat = ft_itoa(WEXITSTATUS(status));
		update_status(env, stat);
		free(stat);
	}
}

void	multi_execution(t_env **env, int process_count, t_shell *cmnds)
{
	t_env	*dash;
	int		saved_in;
	int		saved_out;

	dash = search_key("_", *env);
	set_env_value(&dash, NULL);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	multiple_process_exec(cmnds, process_count, env);
	restore_stds(saved_in, saved_out);
}

void	execute(t_shell *cmnds, t_env **env)
{
	int		process_count;
	int		status;
	pid_t	cpid;

	process_count = how_many_processes(cmnds);
	if (process_count == 1)
		single_process_exec(cmnds, env);
	else
		multi_execution(env, process_count, cmnds);
	while (1)
	{
		cpid = waitpid(-1, &status, 0);
		if (cpid == -1)
		{
			if (errno == ECHILD)
				break ;
			else
			{
				perror("wait");
				exit(-1);
			}
		}
		set_status(env, status, cpid);
	}
}
