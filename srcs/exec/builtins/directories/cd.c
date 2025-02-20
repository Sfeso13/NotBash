/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 12:54:44 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	find_path_nodes(t_env *env, t_env **actual, t_env **hidden)
{
	t_env	*tmp;
	int		count;
	int		found_key;

	count = 0;
	tmp = env;
	found_key = 0;
	while (tmp)
	{
		if (improved_cmp(tmp->key, "PWD") == 0)
		{
			found_key = 1;
			count++;
			*actual = tmp;
		}
		else if (improved_cmp(tmp->key, ".pwd") == 0)
		{
			count++;
			*hidden = tmp;
		}
		if (count == 2)
			break ;
		tmp = tmp->next;
	}
	return (found_key);
}

void	update_oldpwd(t_env *env)
{
	t_env	*dummy;
	t_env	*hidden_pwd;

	find_path_nodes(env, &dummy, &hidden_pwd);
	while (env)
	{
		if (improved_cmp(env->key, "OLDPWD") == 0)
		{
			if (env->val)
				free(env->val);
			env->val = ft_strdup(hidden_pwd->val);
		}
		env = env->next;
	}
}

void	update_pwd(t_env **env)
{
	t_env	*actual;
	t_env	*hidden;
	int		found_key;

	update_oldpwd(*env);
	found_key = find_path_nodes(*env, &hidden, &actual);
	if (found_key)
	{
		if (actual->val)
			free(actual->val);
		if (hidden->val)
			free(hidden->val);
		actual->val = getcwd(NULL, PATH_MAX);
		hidden->val = getcwd(NULL, PATH_MAX);
	}
	else
	{
		envadd_back(env, newenv("PWD", getcwd(NULL, PATH_MAX)));
		if (hidden->val)
			free(hidden->val);
		hidden->val = getcwd(NULL, PATH_MAX);
	}
}

char	*get_home_dir(t_env *env)
{
	while (env)
	{
		if (improved_cmp(env->key, "HOME") == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	changedir(t_shell *cmnds, t_env *env)
{
	char	*homedir;

	if (arr_len(cmnds->args) == 1)
	{
		homedir = get_home_dir(env);
		if (!homedir)
			printf("cd: HOME not set\n");
		else
			chdir(homedir);
	}
	else if (chdir(cmnds->args[1]) == -1)
	{
		printf("cd: %s: no such file or directory\n", cmnds->args[1]);
		return ;//probably should still update pwd but still
	}
	update_pwd(&env);
}
