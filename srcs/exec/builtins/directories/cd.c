/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 23:06:12 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	find_oldpwd_nodes(t_env *env, t_env **actual, t_env **hidden)
{
	t_env	*tmp;
	int		count;
	int		found_key;

	count = 0;
	tmp = env;
	found_key = 0;
	while (tmp)
	{
		if (improved_cmp(tmp->key, "OLDPWD") == 0)
		{
			found_key = 1;
			count++;
			*actual = tmp;
		}
		else if (improved_cmp(tmp->key, ".oldpwd") == 0)
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

int	find_pwd_nodes(t_env *env, t_env **actual, t_env **hidden)
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

void	update_oldpwd(t_env **env)
{
	t_env	*actual;
	t_env	*hidden_pwd;
	int		found;
	t_env	*pwd;

	find_pwd_nodes(*env, &actual, &pwd);
	found = find_oldpwd_nodes(*env, &actual, &hidden_pwd);
	if (found)
	{
		if (actual->val)
			free(actual->val);
		if (hidden_pwd->val)
			free(hidden_pwd->val);
		actual->val = ft_strdup(pwd->val);
		hidden_pwd->val = ft_strdup(pwd->val);
	}
	else
	{
		if (hidden_pwd->val)
			free(hidden_pwd);
		hidden_pwd->val = pwd->val;
	}
}

void	update_pwd(t_env **env)
{
	t_env	*actual;
	t_env	*hidden;
	int		found_key;
	char	*cwd;

	found_key = find_pwd_nodes(*env, &actual, &hidden);
	cwd = getcwd(NULL, PATH_MAX);
	if (!cwd)
		return ;
	free(cwd);
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

void	changedir(t_token *cmnd, t_env *env)
{
	char	*homedir;

	if (how_many_args(cmnd) == 1)
	{
		homedir = get_home_dir(env);
		if (!homedir)
			printf("cd: HOME not set\n");
		else
			chdir(homedir);
	}
	else if (chdir(cmnd->next->value) == -1)
	{
		printf("cd: %s: no such file or directory\n", cmnd->next->value);
		return ;//probably should still update pwd but still
	}
	update_oldpwd(&env);
	update_pwd(&env);
}
