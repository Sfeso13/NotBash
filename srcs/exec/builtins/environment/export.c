/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 11:10:32 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	copy_kv(char *str, t_env *min, size_t len)
{
	size_t	klen;

	klen = ft_strlen(min->key);
	ft_strlcpy(str, min->key, len + 1);
	if (len > klen)
	{
		ft_strlcat(str + klen, "=\"", len + 1);
		ft_strlcat(str + klen + 2, min->val, len + 1);
		ft_strlcat(str + len - 1, "\"", len + 1);
	}
}

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

void	export_env(t_shell *cmnds, t_env *env)
{
	if (arr_len(cmnds->args) == 1)
		print_full_env(dup_env(env));
}
