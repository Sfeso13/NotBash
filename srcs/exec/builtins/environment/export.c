/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 12:18:52 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

char	**env_to_arr(t_env *env)
{
	char	**copy;
	int		i;
	size_t	len;
	t_env	*min;

	i = 0;
	copy = (char **)malloc((env_size(env) + 1) * sizeof(char *));
	if (!copy)
		return (NULL); //FAILURE
	while (env)
	{
		min = get_smallest_k(env);
		len = kv_len(min);
		copy[i] = (char *)malloc(len + 1);
		copy_kv(copy[i], min, len);
		ft_lstdelone(&env, min, free);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	print_full_env(t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = env_to_arr(env);
	while (arr[i])
	{
		printf("declare -x %s\n", arr[i]);
		i++;
	}
	free_tab(arr);
	//free all the tmps
}

int	handle_keys(t_env **env, char **kv, char *equal)
{
	t_env	*key_found;
	char	*key;
	char	*value;

	key_found = search_key(kv[0], *env);
	if (key_found && equal)
		change_value_of_key(&key_found, kv[1]);
	else if (key_found)
		return (1);
	else
	{
		key = kv[0];
		if (!kv[1] && equal)
			value = "";
		else
			value = kv[1];
		envadd_back(env, newenv(key, value));
	}
	return (0);
}

void	export_var(t_shell *cmnds, t_env **env, int args_size)
{
	int		i;
	char	**kv;
	char	*equal;
	t_env	*key_found;

	i = 1;
	while (args_size - 1 > 0)
	{
		equal = ft_strchr(cmnds->args[i], '=');
		kv = kv_extract(cmnds->args[i]);
		key_found = search_key(kv[0], *env);
		handle_keys(env, kv, equal);
		free_tab(kv);
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
