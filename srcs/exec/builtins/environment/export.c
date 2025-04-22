/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/22 15:46:16 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	set_export(t_token *cmnd, t_env **env, char **kv)
{
	char	*equal;
	char	*plus;
	char	*key;

	equal = ft_strchr(cmnd->value, '=');
	plus = ft_strchr(kv[0], '+');
	if (plus)
	{
		key = kv[0];
		kv[0] = ft_strtrim(kv[0], "+=");
		free(key);
		handle_append(env, kv);
	}
	else
	{
		key = kv[0];
		kv[0] = ft_strtrim(kv[0], "=");
		free(key);
		handle_keys(env, kv, equal);
	}
	free_tab(kv);
}

void	print_error(char *s)
{
	ft_putstr_fd("minishell: export : ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	export_var(t_token *cmnd, t_env **env, int args_size)
{
	char	**kv;
	int		status;
	t_token	*cmd_exec;

	status = 0;
	cmd_exec = cmnd;
	while (args_size - 1 > 0)
	{
		kv = export_kv_extract(cmnd->value);
		if (!kv)
			return ;
		if (!validate_key(kv[0]))
		{
			print_error(cmnd->value);
			free_tab(kv);
			status = 1;
		}
		else
			set_export(cmnd, env, kv);
		cmnd = cmnd->next;
		args_size--;
	}
	if (status == 0)
		return (update_status(env, "0"));
	return (update_status(env, "1"));
}

int	how_many_args(t_token *cmnd)
{
	int	count;

	count = 0;
	while (cmnd)
	{
		if (cmnd->type == TOKEN_WORD && (!cmnd->prev || \
			!redir_token(cmnd->prev)))
			count++;
		cmnd = cmnd->next;
	}
	return (count);
}

void	export_env(t_token *cmnd, t_env **env)
{
	int	len;

	len = how_many_args(cmnd);
	if (!cmnd->next || cmnd->next->type != TOKEN_WORD)
		print_full_env(env);
	else
		export_var(cmnd->next, env, len);
}
