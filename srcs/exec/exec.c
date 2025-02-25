/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 21:03:56 by yhossni          ###   ########.fr       */
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
	while (i < process_count)
	{
		fd = get_io_files(cmnds->tokens, env);
		set_fds(&fds, fd, process_count, i);
		piped_exec(cmnds, fds.infd, fds.outfd, env);
		if (fds.infd != -1)
			close(fds.infd);
		fds.infd = fds.pfd[0];
		i++;
		cmnds = cmnds->next;
	}
	close(fds.infd);
	close(fds.pfd[0]);
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
			which_builtin(cmnds, cmnd, env);
		else
			external_cmd(cmnd, env);
	}
}

void	normal_execution(t_shell *cmnds, t_env *env)
{
	t_token *cmnd;
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
	}
}

void	single_process_exec(t_shell *cmnds, t_env *env)
{
	int		saved_in;
	int		saved_out;

	if(is_redirect(cmnds->tokens))
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		redirected_execution(cmnds, env);
		restore_stds(saved_in, saved_out);
	}
	else
		normal_execution(cmnds, env);
}

void	execute(t_shell *cmnds, t_env *env)
{
	int		process_count;
	char	*stat;
	int		status;

	process_count = how_many_processes(cmnds);
	if (process_count == 1)
		single_process_exec(cmnds, env);
	else
		multiple_process_exec(cmnds, process_count, env);
	while (1)
	{
		if (wait(&status) == -1)
		{
			if (errno == ECHILD)
				break ;
			else
			{
				perror("wait");
				exit(-1);
			}
		}
		printf("child exited with : %d\n", status);
		stat = ft_itoa(status);
		update_status(&env, stat);
		free(stat);
	}
}
