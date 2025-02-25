/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:52:18 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 12:31:12 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	run_command(char *path, char **args, t_env *env)
{
	char	**env_arr;

	env_arr = env_to_arr(env);
	execve(path, args, env_arr);
}

int	is_redirect(t_token *cmnd)
{
	if (search_token(cmnd, TOKEN_REDIRECT_IN) || \
		search_token(cmnd, TOKEN_REDIRECT_OUT) || \
		search_token(cmnd, TOKEN_APPEND) || \
		search_token(cmnd, TOKEN_HEREDOC))
		return (1);
	return (0);
}

void	external_cmd(t_shell *shell, t_token *cmnd, t_env *env)
{
	pid_t	child;
	char	*path;
	char	**args;

	child = fork();
	if (child < 0)
		printf("fork error!\n");//to handle appropriately
	else if (child == 0)
	{
		if (is_redirect(shell->tokens))
			redirect(shell->tokens, env);
		args = prepare_args(cmnd);
		path = get_cmnd_path(cmnd, env);
		if (path)
			run_command(path, args, env);
		else
			printf("%s: command not found\n", cmnd->value);
		exit(0);
	}
}
