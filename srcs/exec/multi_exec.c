/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:32:46 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/05 00:06:11 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_fds(t_fd *fds, int *fd, int process_count, int i)
{
	if (pipe(fds->pfd) == -1)
	{
		perror("pipe");
		exit(-1);
	}
	if (!fd)
		return ;
	if (fd[1] == -1 && i < process_count - 1)
		change_fd(&fds->outfd, fds->pfd[1], -1);
	else if (fd[1] == -1 && i == process_count -1)
		change_fd(&fds->outfd, -1, fds->pfd[1]);
	else if (fd[1] != -1)
		change_fd(&fds->outfd, fd[1], fds->pfd[1]);
	if (fd[0] != -1)
		change_fd(&fds->infd, fd[0], -1);
}

void	multi_externals(t_token *cmnd, int *fd, t_fd fds, t_env *env)
{
	char	*path;
	char	**args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = get_cmnd_path(cmnd, env);
	if (!path)
		exit(127);
	if (improved_cmp(path, "permission") == 0)
		exit (126);
	args = prepare_args(cmnd);
	redir_exec(fds);
	(void)fd;
	run_command(path, args, env);
}

void	piped_exec(t_shell *cmnds, int *fd, t_fd fds, t_env **env)
{
	pid_t	child;
	t_token	*cmnd;

	cmnd = extract_cmd(cmnds->tokens);
	child = frk();
	if (child == 0)
	{
		if (!cmnd)
			exit(1);
		if (isbuiltin(cmnd->value))
		{
			redir_exec(fds);
			which_builtin(cmnds, cmnd, env);
			if (improved_cmp(search_key("?", *env)->val, "1") == 0)
				exit (1);
		}
		else
			multi_externals(cmnd, fd, fds, *env);
		exit(0);
	}
	child_pid(child, 1);
	if (fds.infd != -1)
		close(fds.infd);
}

void	multiple_process_exec(t_shell *cmnds, int process_count, t_env **env)
{
	int		i;
	int		*fd;
	t_fd	fds;

	i = 0;
	fds = init_fd_struct();
	fd = init_fds();
	while (i < process_count)
	{
		fd = get_io_files(cmnds->tokens, *env);
		if (!fd && g_signal_received == 1)
		{
			g_signal_received = 0;
			return (update_status(env, "1"));
		}
		set_fds(&fds, fd, process_count, i);
		if (!fd && g_signal_received != 1)
		{
			fd_err(fds, &cmnds, &i);
			continue ;
		}
		execute_p(&fds, fd, &cmnds, env);
		i++;
	}
	closefds(fd, fds);
}
