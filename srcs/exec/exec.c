/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/02 14:07:48 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_status(t_shell *cmnds, t_env **env, int status, pid_t cpid)
{
	char	*stat;

	stat = NULL;
	if (cpid == child_pid(0, 0))
	{
		if (WIFSIGNALED(status))
			stat = ft_itoa(WTERMSIG(status) + 128);
		else if (WIFEXITED(status))
			stat = ft_itoa(WEXITSTATUS(status));
		if (improved_cmp(stat, "0") == 0 || improved_cmp(stat, "130") == 0)
		{
			while (cmnds->next)
				cmnds = cmnds->next;
			update_dash(cmnds->tokens, env);
		}
		update_status(env, stat);
		free(stat);
	}
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
		multiple_process_exec(cmnds, process_count, env);
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
		set_status(cmnds, env, status, cpid);
	}
}
