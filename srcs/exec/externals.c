/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:52:18 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 16:58:50 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	run_command(char *path, char **args, t_env *env)
{
	char	**env_arr;

	env_arr = env_to_arr(env);
	if (!env_arr)
		exit(-1);//check for correct exit status
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

void	external_cmd(t_token *cmnd, t_env *env)
{
	char	*path;
	char	**args;

	path = get_cmnd_path(cmnd, env);
	if (!path)
		exit(127);
	args = prepare_args(cmnd);
	if (!args)
		exit(-1);//check for the correct exit status needed
	run_command(path, args, env);
	exit(0);
}
