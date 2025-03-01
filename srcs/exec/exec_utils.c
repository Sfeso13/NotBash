/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:15:08 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/01 11:43:32 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	set_env_value(t_env **env, char *value)
{
	if ((*env)->val)
		free((*env)->val);
	(*env)->val = value;
}

void	update_dash(t_token *cmnd, t_env **env)
{
	t_env	*tmp;
	t_env	*stat_node;

	stat_node = search_key("?", *env);
	if (stat_node->val && improved_cmp(stat_node->val, "1") == 0)
		return ;
	tmp = *env;
	while (tmp)
	{
		while (cmnd->next && cmnd->next->type == TOKEN_WORD)
			cmnd = cmnd->next;
		if (improved_cmp(tmp->key, "_") == 0)
			set_env_value(&tmp, ft_strdup(cmnd->value));
		tmp = tmp->next;
	}
	if (!search_key("_", *env))
		set_env_value(env, ft_strdup(cmnd->value));
}

t_token	*extract_cmd(t_token *process)
{
	while (process)
	{
		if (process->type == TOKEN_WORD && (!process->prev || \
			process->prev->type == TOKEN_WORD))
			return (process);
		process = process->next;
	}
	return (NULL);
}

int	how_many_processes(t_shell *process)
{
	int	count;

	count = 0;
	while (process)
	{
		count++;
		process = process->next;
	}
	return (count);
}

void	restore_stds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
