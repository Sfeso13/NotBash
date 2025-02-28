/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/28 15:47:37 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

static size_t	len_w(char *s, int equals)
{
	size_t	i;

	i = 0;
	if (*s && *s == '=')
		s++;
	if (equals == 1)
	{
		while (*s && *s != '=')
		{
			s++;
			i++;
		}
	}
	else
	{
		while (*s && *s != '\n')
		{
			s++;
			i++;
		}
	}
	return (i);
}

char	**alloc_arr(char **arr, size_t wlen1, size_t wlen2)
{
	arr[0] = (char *)malloc((wlen1 + 1) * sizeof(char));
	if (!arr[0])
		return (NULL); //malloc failure
	if (wlen2 == 0)
		arr[1] = NULL;
	else
	{
		arr[1] = (char *)malloc((wlen2 + 1) * sizeof(char));
		if (!arr[1])
			return (NULL); //malloc failure
	}
	return (arr);
}

static char	**alluc(char **arr, char *s, size_t wlen1, size_t wlen2)
{
	size_t	i;

	i = 0;
	if (!alloc_arr(arr, wlen1, wlen2))
		return (NULL); //malloc failure
	while (i < wlen1)
		arr[0][i++] = *(s++);
	arr[0][i] = '\0';
	if (*s == '=')
		s++;
	i = 0;
	while (i < wlen2)
		arr[1][i++] = *(s++);
	if (wlen2 != 0)
		arr[1][i] = '\0';
	arr[2] = NULL;
	return (arr);
}

char	**kv_extract(char *var)
{
	char	**arr;
	size_t	wlen1;
	size_t	wlen2;

	wlen1 = 0;
	wlen2 = 0;
	if (var == NULL)
		return (NULL);
	arr = (char **)malloc((3) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	wlen1 = len_w(var, 1);
	if (ft_strchr(var, '='))
		wlen2 = len_w(var + wlen1, 0);
	return (alluc(arr, var, wlen1, wlen2));
}

t_env	*create_env(char *env[])
{
	t_env	*env_list;
	int		i;
	char	**kv_pair; //key value pair

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		kv_pair = kv_extract(env[i]); //TODO: check for failure
		envadd_back(&env_list, newenv(kv_pair[0], kv_pair[1]));
		free_tab(kv_pair);
		i++;
	}
	reset_env(&env_list);
	return (env_list);
}
