/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:29:33 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 11:35:31 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	create_clean_env(t_env **env)
{
	char	buff[PATH_MAX];

	if (!search_key("PWD", *env))
		envadd_back(env, newenv("PWD", getcwd(buff, PATH_MAX)));
	if (!search_key(".pwd", *env))
		envadd_back(env, newenv(".pwd", buff));
	if (!search_key("OLDPWD", *env))
		envadd_back(env, newenv("OLDPWD", NULL));
	if (!search_key(".oldpwd", *env))
		envadd_back(env, newenv(".oldpwd", NULL));
	if (!search_key("SHLVL", *env))
		envadd_back(env, newenv("SHLVL", "1"));
	if (!search_key("_", *env))
		envadd_back(env, newenv("_", "minishell"));
}

void	reset_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if ((improved_cmp(tmp->key, "OLDPWD") == 0) && tmp->val)
		{
			free(tmp->val);
			tmp->val = NULL;
			envadd_back(env, newenv(".oldpwd", NULL));
		}
		else if (improved_cmp(tmp->key, "PWD") == 0)
			envadd_back(env, newenv(".pwd", tmp->val));
		tmp = tmp->next;
	}
	create_clean_env(env);
}
