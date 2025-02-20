/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:53:36 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 09:52:23 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	handle_keys(t_env **env, char **kv, char *equal)
{
	t_env	*key_found;
	char	*key;
	char	*value;

	key_found = search_key(kv[0], *env);
	if (key_found && equal)
	{
		if (!kv[1] && equal)
			key_found->val = ft_strdup("");
		else
			change_value_of_key(&key_found, kv[1]);
	}
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

int	handle_append(t_env **env, char **kv)
{
	t_env	*key_found;
	char	*key;
	char	*value;
	char	*tmp;

	key_found = search_key(kv[0], *env);
	if (key_found)
	{
		tmp = key_found->val;
		value = ft_strjoin(key_found->val, kv[1]);
		free(tmp);
		key_found->val = value;
	}
	else
	{
		key = kv[0];
		if (!kv[1])
			value = "";
		else
			value = kv[1];
		envadd_back(env, newenv(key, value));
	}
	return (0);
}

char	**export_kv_extract(char *var)
{
	char	*equal;
	char	**arr;
	size_t	len;
	int		equal_id;

	if (var == NULL)
		return (NULL);
	arr = (char **)malloc((3) * sizeof(char *));
	equal = ft_strchr(var, '=');
	if (!equal)
	{
		len = ft_strlen(var);
		arr[0] = (char *)malloc(len + 1);
		ft_strlcpy(arr[0], var, len + 1);
		arr[1] = NULL;
	}
	else
	{
		equal_id = equal - var;
		arr[0] = ft_substr(var, 0, equal_id + 1);
		arr[1] = ft_substr(var, equal_id + 1, ft_strlen(var) - equal_id);
	}
	arr[2] = NULL;
	return (arr);
}
