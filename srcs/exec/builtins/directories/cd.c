/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 18:39:16 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	update_oldpwd(t_env **env)
{
	t_env	*actual;
	t_env	*hidden_olpwd;
	t_env	*pwd;

	pwd = search_key(".pwd", *env);
	hidden_olpwd = search_key(".oldpwd", *env);
	actual = search_key("OLDPWD", *env);
	if (actual)
	{
		set_env_value(&actual, ft_strdup(pwd->val));
		set_env_value(&hidden_olpwd, ft_strdup(pwd->val));
	}
	else
		set_env_value(&hidden_olpwd, ft_strdup(pwd->val));

}

void	update_pwd(t_env **env)
{
	t_env	*actual;
	t_env	*hidden;
	char	*cwd;

	actual = search_key("PWD", *env);
	hidden = search_key(".pwd", *env);
	cwd = getcwd(NULL, PATH_MAX);
	if (!cwd)
		return ;
	free(cwd);
	if (actual)
	{
		set_env_value(&actual, getcwd(NULL, PATH_MAX));
		set_env_value(&hidden, getcwd(NULL, PATH_MAX));
	}
	else
		set_env_value(&hidden, getcwd(NULL, PATH_MAX));
}

void	changedir(t_token *cmnd, t_env *env)
{
	t_env	*homedir;

	if (how_many_args(cmnd) == 1)
	{
		homedir = search_key("HOME", env);
		if (!homedir)
		{
			printf("cd: HOME not set\n");
			return (update_status(&env, "1"));
		}
		else
			chdir(homedir->val);
	}
	else if (chdir(cmnd->next->value) == -1)
	{
		printf("cd: %s: no such file or directory\n", cmnd->next->value);
		return (update_status(&env, "1"));//probably should still update pwd but still
	}
	update_status(&env, "0");
	update_oldpwd(&env);
	update_pwd(&env);
}
