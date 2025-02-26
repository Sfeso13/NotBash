/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:17:28 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 20:34:07 by yhossni          ###   ########.fr       */
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
