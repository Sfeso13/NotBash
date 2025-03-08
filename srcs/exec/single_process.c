/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:03:18 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/08 00:54:45 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

int	*single_redirect(t_token *cmnd, t_env *env)
{
	int		*fd;
	t_redir	redir;

	redir = init_redir_struct(cmnd);
	if (!check_doc_limit(redir.in_count[1]))
		return (update_status(&env, "1"), NULL);
	if (search_token(cmnd, TOKEN_HEREDOC))
		process_docs(cmnd, &redir, env);
	fd = get_io_files(cmnd, &redir);
	if (!fd)
		return (NULL);
	if (fd[0] != -1)
	{
		ft_dup(fd[0], 0);
	}
	if (fd[1] != -1)
	{
		ft_dup(fd[1], 1);
	}
	return (fd);
}

void	single_process_exec(t_shell *cmnds, t_env **env)
{
	int		saved_in;
	int		saved_out;

	update_dash(cmnds->tokens, env);
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

int	check_err(int *fd, t_env **env)
{
	if (!fd && g_signal_received == 1)
	{
		g_signal_received = 0;
		update_status(env, "1");
		return (1);
	}
	else if (!fd && g_signal_received == 2)
	{
		g_signal_received = 0;
		update_status(env, "0");
		return (1);
	}
	else if (!fd)
	{
		update_status(env, "1");
		return (1);
	}
	return (0);
}

void	redirected_execution(t_shell *cmnds, t_env **env)
{
	t_token	*cmnd;
	t_env	*dash;
	pid_t	child;
	int		*fd;

	fd = single_redirect(cmnds->tokens, *env);
	if (check_err(fd, env) == 1)
		return ;
	cmnd = extract_cmd(cmnds->tokens);
	if (!cmnd)
	{
		dash = search_key("_", *env);
		return (set_env_value(&dash, NULL));
	}
	if (isbuiltin(cmnd->value))
		which_builtin(cmnds, cmnd, env);
	else
	{
		child = fork();
		if (child < 0)
			perror("fork");
		else if (child == 0)
			external_cmd(cmnd, *env);
		child_pid(child, 1);
	}
}

void	normal_execution(t_shell *cmnds, t_env **env)
{
	t_token	*cmnd;
	t_env	*dash;
	pid_t	child;

	cmnd = extract_cmd(cmnds->tokens);
	if (!cmnd)
	{
		dash = search_key("_", *env);
		return (set_env_value(&dash, NULL));
	}
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
			external_cmd(cmnd, *env);
		child_pid(child, 1);
	}
}
