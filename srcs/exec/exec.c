/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/28 18:12:20 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	multiple_process_exec(t_shell *cmnds, int process_count, t_env *env)
{
	int		i;
	int		*fd;
	t_fd	fds;

	i = 0;
	fds = init_fd_struct();
	fd = init_fds();
	while (i < process_count)
	{
		fd = get_io_files(cmnds->tokens, env);
		set_fds(&fds, fd, process_count, i);
		if (!fd)
		{
			close(fds.pfd[1]);
			fds.infd = fds.pfd[0];
			cmnds = cmnds->next;
			i++;
			continue ;
		}
		piped_exec(cmnds, fd, fds, env);
		fds.infd = fds.pfd[0];
		i++;
		cmnds = cmnds->next;
	}
	closefds(fd, fds);
}

void	redirected_execution(t_shell *cmnds, t_env *env)
{
	t_token	*cmnd;
	t_env	*dash;
	pid_t	child;

	child = fork();
	if (child < 0)
		perror("fork");
	else if (child == 0)
	{
		redirect(cmnds->tokens, env);
		cmnd = extract_cmd(cmnds->tokens);
		if (!cmnd)
		{
			dash = search_key("_", env);
			return (set_env_value(&dash, NULL));
		}
		update_dash(cmnd, &env);
		if (isbuiltin(cmnd->value))
			exec_builtins(cmnds, cmnd, env);
		else
			external_cmd(cmnd, env);
		exit(0);
	}
	child_pid(child, 1);
}

void	normal_execution(t_shell *cmnds, t_env *env)
{
	t_token	*cmnd;
	t_env	*dash;
	pid_t	child;

	cmnd = extract_cmd(cmnds->tokens);
	if (!cmnd)
	{
		dash = search_key("_", env);
		return (set_env_value(&dash, NULL));
	}
	update_dash(cmnd, &env);
	if (isbuiltin(cmnd->value))
		which_builtin(cmnds, cmnd, env);
	else
	{
		child = fork();
		if (child < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (child == 0)
			external_cmd(cmnd, env);
		child_pid(child, 1);
	}
}

void	single_process_exec(t_shell *cmnds, t_env *env)
{
	int		saved_in;
	int		saved_out;

	if (is_redirect(cmnds->tokens))
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		redirected_execution(cmnds, env);
		restore_stds(saved_in, saved_out);
	}
	else
		normal_execution(cmnds, env);
}

void	set_status(t_env **env, int status, pid_t cpid)
{
	char	*stat;

	stat = NULL;
	if (cpid == child_pid(0, 0))
	{
		if (WIFSIGNALED(status))
			stat = ft_itoa(WTERMSIG(status) + 128);
		else if (WIFEXITED(status))
			stat = ft_itoa(WEXITSTATUS(status));
		update_status(env, stat);
		free(stat);
	}
}

void	execute(t_shell *cmnds, t_env *env)
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
		set_status(&env, status, cpid);
	}
}
