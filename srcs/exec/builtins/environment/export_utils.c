/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:19 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 11:01:10 by yhossni          ###   ########.fr       */
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
