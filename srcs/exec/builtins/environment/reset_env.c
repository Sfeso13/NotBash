/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:29:33 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/03 15:33:18 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

char	*get_wd()
{
	char	*buff;

	buff = getcwd(NULL, PATH_MAX);
	if (!buff)
		perror("minishell");
	return (buff);
}

// void	create_clean_env(t_env **env)
// {
// 	char	*buff;

// 	buff = get_wd();
// 	if (!search_key("PWD", *env))
// 	{
// 		envadd_back(env, newenv("PWD", buff));
// 		search_key("PWD", *env)->is_set = 0;
// 	}
// 	if (!search_key("OLDPWD", *env))
// 	{
// 		envadd_back(env, newenv("OLDPWD", NULL));
// 		search_key("OLDPWD", *env)->is_set = 0;
// 	}
// 	if (!search_key("SHLVL", *env))
// 		envadd_back(env, newenv("SHLVL", "1"));
// 	if (!search_key("_", *env))
// 		envadd_back(env, newenv("_", "minishell"));
// 	if (!search_key("?", *env))
// 	{
// 		envadd_back(env, newenv("?", NULL));
// 		search_key("?", *env)->is_set = 0;
// 	}
// 	if (!search_key("PATH", *env))
// 	{
// 		envadd_back(env, newenv("PATH", \
// 		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
// 		search_key("PATH", *env)->is_set = 0;
// 	}
// 	free(buff);
// }

void	hide_vars(char *key, char *value, t_env **env)
{
	if (!search_key(key, *env))
		envadd_back(env, newenv(key, value, 0));
}

void	reset_env(t_env **env)
{
	char	*buff;

	buff = get_wd();
	if (!search_key("PWD", *env))
		envadd_back(env, newenv("PWD", buff, 1));
	if (!search_key("OLDPWD", *env))
		envadd_back(env, newenv("OLDPWD", NULL, 1));
	if (!search_key("?", *env))
		envadd_back(env, newenv("?", NULL, 0));
	if (!search_key("SHLVL", *env))
		envadd_back(env, newenv("SHLVL", "1", 1));
	if (!search_key("_", *env))
		envadd_back(env, newenv("_", "minishell", 1));
	if (!search_key("PATH", *env))
		envadd_back(env, newenv("PATH", \
		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), 0));
	free(buff);
}
