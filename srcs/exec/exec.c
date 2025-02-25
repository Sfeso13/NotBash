/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 15:51:47 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

t_token	*search_token(t_token *token, t_token_type type)
{
	while (token)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}

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
		printf("input : %d ---------- output : %d\n", fds.infd, fds.outfd);
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

void	single_process_exec(t_shell *cmnds, t_env *env)
{
	t_token	*cmnd;
	t_env	*dash;

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
		external_cmd(cmnds, cmnd, env);
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
		stat = ft_itoa(status);
		update_status(&env, stat);
		free(stat);
	}
}
