/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:32:46 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 21:04:04 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	redir_exec(t_fd fds)
{
	if (fds.infd != -1)
		ft_dup(fds.infd, 0);
	if (fds.outfd != -1)
		ft_dup(fds.outfd, 1);
	close(fds.pfd[0]);
}

void	multi_externals(t_token *cmnd, int *fd, t_fd fds, t_env *env)
{
	char	*path;
	char	**args;

	path = get_cmnd_path(cmnd, env);
	if (!path)
		exit(127);
	args = prepare_args(cmnd);
	redir_exec(fds);
	(void)fd;
	run_command(path, args, env);
}

void	piped_exec(t_shell *cmnds, int *fd, t_fd fds, t_env *env)
{
	pid_t	child;
	t_token	*cmnd;

	cmnd = extract_cmd(cmnds->tokens);
	child = fork();
	if (child < 0)
		printf("fork error!\n");//to handle appropriately
	else if (child == 0)
	{
		if (!cmnd)
			exit(1);
		if (isbuiltin(cmnd->value))
		{
			redir_exec(fds);
			which_builtin(cmnds, cmnd, env);
		}
		else
			multi_externals(cmnd, fd, fds, env);
		exit(0);
	}
	if (fds.infd != -1)
		close(fds.infd);
}

void	change_fd(int *tochange, int toset, int toclose)
{
	if (*tochange != -1)
		close(*tochange);
	*tochange = toset;
	if (toclose != -1)
		close(toclose);
}

t_fd	init_fd_struct(void)
{
	t_fd	fds;

	fds.infd = -1;
	fds.outfd = -1;
	fds.pfd[0] = -1;
	fds.pfd[1] = -1;
	return (fds);
}

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
