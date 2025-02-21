/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 22:33:36 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	export_var(t_token *cmnd, t_env **env, int args_size)
{
	int		i;
	char	**kv;
	char	*equal;
	char	*plus;

	i = 1;
	while (args_size - 1 > 0)
	{
		kv = export_kv_extract(cmnd->args[i]);
		kv[0] = validate_key(kv[0]);
		if (kv[0] == NULL || !kv[0][0])
			printf("invalid id : %s\n", cmnd->args[i]); //INVALID ID
		else
		{
			equal = ft_strchr(cmnd->args[i], '=');
			plus = ft_strchr(cmnd->args[i], '+');
			if (plus)
				handle_append(env, kv);
			else
				handle_keys(env, kv, equal);
			free_tab(kv);
		}
		i++;
		args_size--;
	}
}

int	how_many_args(t_token *cmnd)
{
	int	count;

	count = 0;
	while (cmnd->type == TOKEN_WORD)
	{
		count++;
		cmnd = cmnd->next;
	}
	return (count);
}

void	export_env(t_token *cmnd, t_env *env)
{
	int	len;

	// len = arr_len(cmnd->args);
	len = how_many_args();
	if (!cmnd->next || cmnd->next->type != TOKEN_WORD)
		print_full_env(dup_env(env));
	else
		export_var(cmnd, &env);
}
