/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:19 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 18:16:07 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

size_t	kv_len(t_env *env)
{
	size_t	klen;
	size_t	vlen;

	klen = 0;
	vlen = 0;
	if (env->key)
		klen = ft_strlen(env->key);
	if (env->val)
		vlen = ft_strlen(env->val) + 3;
	return (klen + vlen);
}

t_env	*get_smallest_k(t_env *env)
{
	t_env	*min;

	min = env;
	while (env)
	{
		if (ft_strncmp(min->key, env->key, ft_strlen(env->key)) > 0)
			min = env;
		env = env->next;
	}
	return (min);
}

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

t_env	*search_key(char *key, t_env *env)
{
	while (env)
	{
		if (improved_cmp(key, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	change_value_of_key(t_env **tochange, char *value)
{
	free((*tochange)->val);
	(*tochange)->val = ft_strdup(value);
}
