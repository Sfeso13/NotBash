/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:17:42 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/04 15:18:09 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <

void	fd_err(t_fd fds, t_shell *cmnds, int *i)
{
	g_signal_received = 0;
	close(fds.pfd[1]);
	fds.infd = fds.pfd[0];
	cmnds = cmnds->next;
	(*i)++;
}

void	execute_p(t_fd fds, int *fd, t_shell **cmnds, t_env **env)
{
	piped_exec(cmnds, fd, fds, env);
	fds.infd = fds.pfd[0];
	*cmnds = (*cmnds)->next;
}
