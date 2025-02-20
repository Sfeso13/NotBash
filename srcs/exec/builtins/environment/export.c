/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 09:51:58 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	export_var(t_shell *cmnds, t_env **env, int args_size)
{
	int		i;
	char	**kv;
	char	*equal;
	char	*plus;

	i = 1;
	while (args_size - 1 > 0)
	{
		kv = export_kv_extract(cmnds->args[i]);
		kv[0] = validate_key(kv[0]);
		if (kv[0] == NULL || !kv[0][0])
			printf("invalid id : %s\n", cmnds->args[i]); //INVALID ID
		else
		{
			equal = ft_strchr(cmnds->args[i], '=');
			plus = ft_strchr(cmnds->args[i], '+');
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

void	export_env(t_shell *cmnds, t_env *env)
{
	int	len;

	len = arr_len(cmnds->args);
	if (len == 1)
		print_full_env(dup_env(env));
	else if (len > 1)
		export_var(cmnds, &env, len);
}
