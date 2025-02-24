/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/24 16:50:34 by yhossni          ###   ########.fr       */
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
	int	pfd[2];
	int	fd[2];

	while (process_count > 0)
	{
		if (is_redirect(cmnds))
		
		if (pipe(pfd) == -1)
		{
			perror("pipe");
			exit(-1);
		}
		process_count--;
	}
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

	process_count = how_many_processes(cmnds);
	if (process_count == 1)
		single_process_exec(cmnds, env);
	else
		multiple_process_exec(cmnds, process_count, env);
}
