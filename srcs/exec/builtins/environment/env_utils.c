/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:51:33 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 12:09:01 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst && new)
	{
		tmp = findlast_env(*lst);
		if (!tmp)
		{
			*lst = new;
			return ;
		}
		tmp->next = new;
		new->prev = tmp;
	}
}

t_env	*findlast_env(t_env *lst)
{
	while (lst)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*newenv(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = ft_strdup(key);
	node->val = ft_strdup(value);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*dup_env(t_env *env)
{
	t_env	*dup;

	dup = NULL;
	while (env)
	{
		if (improved_cmp(env->key, "_") != 0)
			envadd_back(&dup, newenv(env->key, env->val));
		env = env->next;
	}
	return (dup);
}

// void	create_clean_env(t_env **env)
// {
// 	char	buff[PATH_MAX];

// 	envadd_back(env, newenv("PWD", getcwd(buff, PATH_MAX)));
// 	envadd_back(env, newenv(".pwd", buff));
// 	envadd_back(env, newenv("OLDPWD", NULL));
// 	envadd_back(env, newenv(".oldpwd", NULL));
// 	envadd_back(env, newenv("SHLVL", "1"));
// 	envadd_back(env, newenv("_", "minishell"));
// }

// void	reset_env(t_env **env)
// {
// 	t_env	*tmp;
// 	int		foundpwd;
// 	int		foundoldpwd;

// 	tmp = *env;
// 	if (!tmp)
// 		create_clean_env(env);
// 	while (tmp)
// 	{
// 		if ((improved_cmp(tmp->key, "OLDPWD") == 0) && tmp->val)
// 		{
// 			free(tmp->val);
// 			tmp->val = NULL;
// 			envadd_back(env, newenv(".oldpwd", NULL));
// 		}
// 		else if (improved_cmp(tmp->key, "PWD") == 0)
// 			envadd_back(env, newenv(".pwd", tmp->val));
// 		tmp = tmp->next;
// 	}
// }
