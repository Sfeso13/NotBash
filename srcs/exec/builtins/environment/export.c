/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/17 12:18:49 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

size_t	kv_len(t_env *env)
{
	size_t	klen;
	size_t	vlen;

	if (env->key)
		klen = ft_strlen(env->key);
	if (env->val)
		vlen = ft_strlen(env->val) + 3;
	return (klen + vlen);
}

char	**env_to_arr(t_env *env)
{
	int		size;
	char	**copy;
	int		i;
	size_t	len;
	size_t	klen;

	i = 0;
	size = env_size(env);
	copy = (char **)malloc((size + 1) * sizeof(char*));
	if (!copy)
		return (NULL); //FAILURE
	while (env)
	{
		klen = ft_strlen(env->key);
		len = kv_len(env);
		copy[i] = (char *)malloc(len + 1);
		if (!copy[i])
			return (NULL); //FAILURE (prob add safe free)
		ft_strlcpy(copy[i], env->key, len + 1);
		if (len > klen)
		{
			ft_strlcat(copy[i] + klen, "=\"", len + 1);
			ft_strlcat(copy[i] + klen + 2, env->val, len + 1);
			ft_strlcat(copy[i] + len - 1, "\"", len + 1);
		}
		i++;
		env = env->next;
	}
	copy[i] = NULL;
	return (copy);
}

t_env	*order_env(t_env *env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = env_to_arr(env);
	while (arr[i])
	{
		
	}
}

void	print_full_env(t_env *env)
{
	t_env	*tmp;

	tmp = order_env(env);
}

void	export_env(t_shell *cmnds, t_env *env)
{
	if (arr_len(cmnds->args) == 1)
		print_full_env(env);
}
