/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 18:18:50 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_env_value(t_env **env, char *value)
{
	if ((*env)->val)
		free((*env)->val);
	(*env)->val = value;
}

void	update_dash(t_shell *cmnds, t_env **env)
{
	int		len;
	t_env	*tmp;

	tmp = *env;
	len = arr_len(cmnds->args);
	while (tmp)
	{
		if (improved_cmp(tmp->key, "_") == 0)
			set_env_value(&tmp, ft_strdup(cmnds->args[len - 1]));
		tmp = tmp->next;
	}
}

void	which_builtin(t_shell *cmnds, t_env *env)
{
	update_dash(cmnds, &env);
	if (improved_cmp(cmnds->args[0], "env") == 0)
		print_env(env);
	else if (improved_cmp(cmnds->args[0], "export") == 0)
		export_env(cmnds, env);
	else if (improved_cmp(cmnds->args[0], "unset") == 0)
		unset_var(cmnds, env);
	else if (improved_cmp(cmnds->args[0], "pwd") == 0)
		print_current_dir();
	else if (improved_cmp(cmnds->args[0], "cd") == 0)
		changedir(cmnds, env);
	else if (improved_cmp(cmnds->args[0], "echo") == 0)
		print_args(cmnds);
	else
		printf("other builtins\n");
}

void	execute(t_shell *cmnds, t_env *env)
{
	if (cmnds->is_buiultin)
		which_builtin(cmnds, env);
}
