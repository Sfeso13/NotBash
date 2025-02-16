/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 12:31:29 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

static size_t	len_w(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	if (c == '=')
	{
		while (*s && *s != c)
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

static char	**alluc(char **arr, char *s)
{
	size_t	i;
	size_t	wlen1;
	size_t	wlen2;
	char 	*tmp;

	i = 0;
	tmp = s;
	wlen1 = len_w(s, '=');
	wlen2 = len_w(s, 'x');
	arr[0] = (char *)malloc((wlen1 + 1) * sizeof(char));
	if (!arr[0])
		return (NULL); //malloc failure
	arr[1] = (char *)malloc((wlen2 + 1) * sizeof(char));
	if (!arr[1])
		return (NULL); //malloc failure
	while (i < wlen1)
		arr[0][i++] = *(s++);
	arr[0][i] = '\0';
	while (*s == '=')
		s++;
	i = 0;
	while (i < wlen2)
		arr[1][i++] = *(s++);
	arr[1][i] = '\0';
	arr[2] = NULL;
	return (arr);
}

char	**kv_extract(char *var)
{
	char	**arr;

	if (var == NULL)
		return (NULL);
	arr = (char **)malloc((3) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (alluc(arr, var));
}

void	free_tab(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_env	*create_env(char *env[])
{
	int		i;
	char	**kv_pair; //key value pair
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		kv_pair = kv_extract(env[i]); //TODO: check for failure
		envadd_back(&env_list, newenv(kv_pair[0], kv_pair[1]));
		free_tab(kv_pair);
		i++;
	}
	return (env_list);
}
