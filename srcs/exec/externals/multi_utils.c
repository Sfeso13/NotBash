/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:17:28 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/01 11:25:24 by yhossni          ###   ########.fr       */
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

void	exec_builtins(t_shell *shell, t_token *cmnd, t_env **env)
{
	t_env	*status_node;

	status_node = search_key("?", *env);
	if (improved_cmp(cmnd->value, "env") == 0)
		print_env(*env);
	else if (improved_cmp(cmnd->value, "export") == 0)
		export_env(cmnd, *env);
	else if (improved_cmp(cmnd->value, "unset") == 0)
		unset_var(cmnd, env);
	else if (improved_cmp(cmnd->value, "pwd") == 0)
		print_current_dir(*env);
	else if (improved_cmp(cmnd->value, "cd") == 0)
		changedir(cmnd, *env);
	else if (improved_cmp(cmnd->value, "echo") == 0)
		print_args(cmnd, *env);
	else if (improved_cmp(cmnd->value, "exit") == 0)
		exit_shell(&shell, &cmnd, env);
	if (status_node && status_node->val && \
		improved_cmp(status_node->val, "1") == 0)
		exit (1);
	exit (0);
}

void	redir_exec(t_fd fds)
{
	if (fds.infd != -1)
		ft_dup(fds.infd, 0);
	if (fds.outfd != -1)
		ft_dup(fds.outfd, 1);
	close(fds.pfd[0]);
}
