/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:58:38 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/05 15:31:56 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

char	**env_to_arr_export(t_env *env)
{
	char	**copy;
	int		i;
	size_t	len;
	t_env	*min;

	i = 0;
	copy = (char **)malloc((env_size(env) + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (env)
	{
		min = get_smallest_k(env);
		if (min->is_set)
		{
			len = kv_len(min);
			copy[i] = (char *)malloc(len + 1);
			if (!copy[i])
				safe_free(copy, i);
			copy_kv_export(copy[i], min, len);
			i++;
		}
		delone_env(&env, min, free);
	}
	copy[i] = NULL;
	return (copy);
}

void	print_full_env(t_env **env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = env_to_arr_export(dup_env(*env));
	if (!arr)
		return (update_status(env, "1"));
	while (arr[i])
	{
		printf("declare -x %s\n", arr[i]);
		i++;
	}
	free_tab(arr);
	update_status(env, "0");
}
