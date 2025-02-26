/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:59:17 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 15:13:02 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	redir_token(t_token *cmnd)
{
	if (cmnd->type == TOKEN_REDIRECT_IN || cmnd->type == TOKEN_REDIRECT_OUT || \
		cmnd->type == TOKEN_APPEND || cmnd->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

char	**prepare_args(t_token *cmnd)
{
	char	*args;
	char	*tmp;
	char	**arr;

	args = NULL;
	while (cmnd)
	{
		if (cmnd->type == TOKEN_WORD && (!cmnd->prev || !redir_token(cmnd->prev)))
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
		printf("%s: command not found\n", cmnd->value);
		return (NULL);
	}
	else
	{
		path_node = search_key("PATH", env);
		if (path_node && path_node->val && path_node->val[0] != '\0')
		{
			paths = args_split(path_node->val, ':');
			if (!paths)
				return (NULL); //FAILURE
			correct_path = retrieve_path(paths, cmnd);
			if (!correct_path)
			{
				printf("%s: command not found\n", cmnd->value);
				return (NULL);
			}
		}
		else if (!path_node || path_node->val[0] == '\0')
		{
			printf("%s: No such file or directory\n", cmnd->value);
			return (NULL);//should be different error msg than cmd not found
		}
	}
	return (correct_path);
}
