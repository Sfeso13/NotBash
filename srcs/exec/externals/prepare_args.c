/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:59:17 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 13:20:48 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

char	**prepare_args(t_token *cmnd)
{
	char	*args;
	char	*tmp;
	char	**arr;

	args = NULL;
	while (cmnd && cmnd->type == TOKEN_WORD)
	{
		tmp = args;
		args = join(tmp, cmnd->value);
		free(tmp);
		if (!args)
			return (NULL);
		cmnd = cmnd->next;
	}
	arr = args_split(args, ' ');
	return (arr);
}

char	*retrieve_path(char **paths, t_token *cmnd)
{
	char	*correct_path;
	char	*tmp;
	int		i;

	i = 0;
	correct_path = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin(tmp, cmnd->value);
		free(tmp);
		if (!correct_path)
			break ;
		if (access(correct_path, X_OK) == 0)
			break ;
		free(correct_path);
		correct_path = NULL;
		i++;
	}
	free_tab(paths);
	return (correct_path);
}

char	*get_cmnd_path(t_token *cmnd, t_env *env)
{
	char	**paths;
	char	*correct_path;
	t_env	*path_node;

	correct_path = NULL;
	if (ft_strchr(cmnd->value, '/'))
	{
		if (access(cmnd->value, X_OK) == 0)
			return (cmnd->value);
		return (NULL);
	}
	else
	{
		path_node = search_key("PATH", env);
		if (path_node && path_node->val)
		{
			paths = args_split(path_node->val, ':');
			if (!paths)
				return (NULL); //FAILURE
			correct_path = retrieve_path(paths, cmnd);
		}
		else if (!path_node || path_node->val[0] == '\0')
			return (NULL);//should be different error msg than cmd not found
	}
	return (correct_path);
}
