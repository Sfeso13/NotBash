/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:17:28 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/01 12:08:32 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

void	closefds(int *fd, t_fd fds)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fds.pfd[1] != -1)
		close(fds.pfd[1]);
	if (fds.pfd[0] != -1)
		close(fds.pfd[0]);
	if (fds.infd != -1)
		close(fds.infd);
	if (fds.outfd != -1)
		close(fds.outfd);
}

void	redir_exec(t_fd fds)
{
	if (fds.infd != -1)
		ft_dup(fds.infd, 0);
	if (fds.outfd != -1)
		ft_dup(fds.outfd, 1);
	close(fds.pfd[0]);
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
