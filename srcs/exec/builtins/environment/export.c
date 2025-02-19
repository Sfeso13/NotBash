/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:50:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/19 17:03:02 by yhossni          ###   ########.fr       */
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

int	allowed(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] >= 'a' && c[i] <= 'z')|| (c[i] >= 'A' && c[i] <='Z') || c[i] == '_' || \
			(c[i] >= '0' && c[i] <= '9') || c[i] == '+' || c[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_plus(char *s)
{
	int	i;
	int	count;
	char	*plus;

	i = 0;
	count = 0;
	plus = NULL;
	while (s[i])
	{
		if (s[i] == '+')
			count++;
		i++;
	}
	if (count > 0)
		plus = ft_strchr(s, '+');
	if (plus && count == 1)
	{
		if (*(plus + 1) != '=')
			return (-1);
	}
	return (count);
}

char	*validate_key(char *key)
{
	int		i;
	int		plus;
	size_t	len;
	char	*res;

	i = 0;
	if (!allowed(key))
	{
		free(key);
		return (NULL);
	}
	len = ft_strlen(key);
	plus = is_plus(key);
	if (plus > 1 || plus == -1)
	{
		free(key);
		return (NULL);
	}
	else if ((plus && (key[len - 2] != '+')) || \
		(key[0] >= '0' && key[0] <= '9'))
	{
		free(key);
		return (NULL);
	}
	res = ft_strtrim(key, "+=");
	free(key);
	return (res);
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
		equal_id =  equal - var;
		arr[0] = ft_substr(var, 0, equal_id + 1);
		arr[1] = ft_substr(var, equal_id + 1, ft_strlen(var) - equal_id);
	}
	arr[2] = NULL;
	return (arr);
}

void	export_var(t_shell *cmnds, t_env **env, int args_size)
{
	int		i;
	char	**kv;
	char	*equal;
	char	*plus;

	i = 1;
	printf("dummy shit %s\n", (*env)->key);
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
