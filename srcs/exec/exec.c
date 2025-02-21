/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 22:09:36 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_env_value(t_env **env, char *value)
{
	if ((*env)->val)
		free((*env)->val);
	(*env)->val = value;
}

// void	update_dash(t_shell *cmnds, t_env **env)
// {
// 	int		len;
// 	t_env	*tmp;

// 	tmp = *env;
// 	len = arr_len(cmnds->args);
// 	while (tmp)
// 	{
// 		if (improved_cmp(tmp->key, "_") == 0)
// 			set_env_value(&tmp, ft_strdup(cmnds->args[len - 1]));
// 		tmp = tmp->next;
// 	}
// }

void	which_builtin(t_token *cmnd, t_env *env)
{
	// update_dash(cmnd, &env);
	if (improved_cmp(cmnd->value, "env") == 0)
		print_env(env);
	else if (improved_cmp(cmnd->value, "export") == 0)
		export_env(cmnd, env);
	// else if (improved_cmp(cmnd->value, "unset") == 0)
	// 	unset_var(cmnds, env);
	// else if (improved_cmp(cmnd->value, "pwd") == 0)
	// 	print_current_dir(env);
	// else if (improved_cmp(cmnd->value, "cd") == 0)
	// 	changedir(cmnds, env);
	// else if (improved_cmp(cmnd->value, "echo") == 0)
	// 	print_args(cmnds);
	// else if (improved_cmp(cmnd->value, "exit") == 0)
	// 	exit_shell(&cmnds, &env);
	else
		printf("other builtins\n");
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

t_token	*extract_cmd(t_token *process)
{
	while (process)
	{
		if (process->type == TOKEN_WORD)
			return (process);
		process = process->next;
	}
	return (NULL);
}

void	execute(t_shell *cmnds, t_env *env)
{
	t_token	*cmnd;

	cmnd = extract_cmd(cmnds->tokens);
	if (isbuiltin(cmnd->value))
		which_builtin(cmnd, env);
}
