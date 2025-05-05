/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:15:08 by yhossni           #+#    #+#             */
/*   Updated: 2025/05/05 14:54:35 by yhossni          ###   ########.fr       */
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
	t_env	*dash;
	int		len;

	tmp = *env;
	len = how_many_args(cmnd);
	while (cmnd && len > 1)
	{
		if (cmnd->type == TOKEN_WORD && (!cmnd->prev || \
			!redir_token(cmnd->prev)))
			len--;
		cmnd = cmnd->next;
	}
	dash = search_key("_", *env);
	if (dash)
		set_env_value(&dash, ft_strdup(cmnd->value));
	else
		envadd_back(env, newenv("_", cmnd->value, 1));
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
	if (dup2(saved_in, STDIN_FILENO) == -1)
		perror("stdin restore failed");
	if (dup2(saved_out, STDOUT_FILENO) == -1)
		perror("stdout restore failed");
	close(saved_in);
	close(saved_out);
}
