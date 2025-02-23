/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 12:50:08 by yhossni          ###   ########.fr       */
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

void	run_command(int *fd, char *path, char **args, t_env *env)
{
	char	**env_arr;

	(void)fd;
	env_arr = env_to_arr(env);
	execve(path, args, env_arr);
}

void	external_cmd(t_shell *shell, t_token *cmnd, t_env *env)
{
	int		*fd;
	pid_t	child;
	int		status;
	char	*path;
	char	**args;

	child = fork();
	if (child < 0)
		printf("fork error!\n");//to handle appropriately
	else if (child == 0)
	{
		if (search_token(cmnd, TOKEN_REDIRECT_IN) || \
			search_token(cmnd, TOKEN_REDIRECT_OUT) || \
			search_token(cmnd, TOKEN_APPEND))
			fd = get_io_files(shell->tokens);
		args = prepare_args(cmnd);
		path = get_cmnd_path(cmnd, env);
		if (path)
			run_command(fd, path, args, env);
		else
			printf("%s: command not found\n", cmnd->value);
		exit(0);
	}
	else
	{
		wait(&status);
		update_status(&env, ft_itoa(status));
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
}
