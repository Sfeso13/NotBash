/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:21:30 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/02 17:21:53 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

// void	save_last_cmd(t_token *cmnd , t_env **env)
// {
// 	t_env	*status;

// 	status = search_key("?", *env);
// 	if (status && status->val)
// 	{
// 		if (improved_cmp(status->val, "0") == 0)
// 			update_dash(cmnd, env);
// 	}
// }

void	which_builtin(t_shell *shell, t_token *cmnd, t_env **env)
{
	if (improved_cmp(cmnd->value, "env") == 0)
		print_env(env);
	else if (improved_cmp(cmnd->value, "export") == 0)
		export_env(cmnd, env);
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
}

int	isbuiltin(char *com)
{
	const char	*builtins[] = {"pwd", "echo", "cd", "export",
		"unset", "env", "exit", NULL};
	int			i;

	i = 0;
	if (!com)
		return (0);
	while (builtins[i])
	{
		if (ft_strcmp(com, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
