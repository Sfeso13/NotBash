/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:59:17 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/27 14:59:07 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

char	**prepare_args(t_token *cmnd)
{
	char	*args;
	char	*tmp;
	char	**arr;

	args = NULL;
	while (cmnd)
	{
		if (cmnd->type == TOKEN_WORD && (!cmnd->prev || \
			!redir_token(cmnd->prev)))
		{
			tmp = args;
			args = join(tmp, cmnd->value);
			free(tmp);
			if (!args)
				return (NULL);
		}
		cmnd = cmnd->next;
	}
	arr = args_split(args, ' ');
	free(args);
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
		if (!tmp)
			break ;
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

int	is_absolute(t_token *cmnd)
{
	if (ft_strchr(cmnd->value, '/'))
	{
		if (access(cmnd->value, X_OK) == 0)
			return (1);
		printf("%s: command not found\n", cmnd->value);
		return (-1);
	}
	return (0);
}

char	*path(t_env *path_node, t_token *cmnd)
{
	char	**paths;
	char	*correct_path;

	paths = args_split(path_node->val, ':');
	if (!paths)
		return (NULL);
	correct_path = retrieve_path(paths, cmnd);
	if (!correct_path)
	{
		printf("%s: command not found\n", cmnd->value);
		free_tab(paths);
		return (NULL);
	}
	return (correct_path);
}

char	*get_cmnd_path(t_token *cmnd, t_env *env)
{
	char	*correct_path;
	t_env	*path_node;
	int		absolute;

	correct_path = NULL;
	absolute = is_absolute(cmnd);
	if (absolute == 1)
		return (cmnd->value);
	if (absolute == -1)
		return (NULL);
	path_node = search_key("PATH", env);
	if (path_node && path_node->val && path_node->val[0] != '\0')
		correct_path = path(path_node, cmnd);
	else if (!path_node || !path_node->val || path_node->val[0] == '\0')
	{
		printf("%s: No such file or directory\n", cmnd->value);
		return (NULL);
	}
	return (correct_path);
}
