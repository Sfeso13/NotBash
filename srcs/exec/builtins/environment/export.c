/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 10:40:52 by yhossni          ###   ########.fr       */
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

char	**env_to_arr(t_env *env)
{
	int		size;
	char	**copy;
	int		i;
	size_t	len;
	size_t	klen;
	t_env	*tmp;
	t_env	*min;

	i = 0;
	tmp = env;
	size = env_size(tmp);
	copy = (char **)malloc((size + 1) * sizeof(char*));
	if (!copy)
		return (NULL); //FAILURE
	while (tmp)
	{
		min = get_smallest_k(tmp);
		klen = ft_strlen(min->key);
		len = kv_len(min);
		copy[i] = (char *)malloc(len + 1);
		ft_strlcpy(copy[i], min->key, len + 1);
		if (len > klen)
		{
			ft_strlcat(copy[i] + klen, "=\"", len + 1);
			ft_strlcat(copy[i] + klen + 2, min->val, len + 1);
			ft_strlcat(copy[i] + len - 1, "\"", len + 1);
		}
		ft_lstdelone(&tmp, min, free);
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
	//free all the tmps
}

t_env	*dup_env(t_env *env)
{
	t_env *dup;

	dup = NULL;
	while (env)
	{
		if (improved_cmp(env->key,"_") != 0)
			envadd_back(&dup, newenv(env->key, env->val));
		env = env->next;
	}
	return (dup);
}

void	export_env(t_shell *cmnds, t_env *env)
{
	if (arr_len(cmnds->args) == 1)
		print_full_env(dup_env(env));
}
