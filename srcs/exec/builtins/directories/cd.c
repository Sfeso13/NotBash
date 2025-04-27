/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/27 15:18:33 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"
#include <sys/stat.h>

void	update_oldpwd(t_env **env)
{
	t_env	*actual;
	t_env	*pwd;

	pwd = search_key("PWD", *env);
	if (!pwd->val)
		pwd = search_key(".pwd", *env);
	actual = search_key("OLDPWD", *env);
	if (actual)
		set_env_value(&actual, ft_strdup(pwd->val));
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
		set_env_value(&actual, getcwd(NULL, PATH_MAX));
	if (hidden)
		set_env_value(&hidden, getcwd(NULL, PATH_MAX));
}

int	go_to(t_token *cmnd)
{
	char	*path;
	char	cwd[1024];

	while (cmnd)
	{
		if (cmnd->type == TOKEN_WORD && cmnd->prev && !redir_token(cmnd->prev))
			break ;
		cmnd = cmnd->next;
	}
	path = cmnd->value;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	return (chdir(path));
}

void	changedir(t_token *cmnd, t_env *env)
{
	t_env	*homedir;

	if (how_many_args(cmnd) == 1)
	{
		homedir = search_key("HOME", env);
		if (!homedir)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (update_status(&env, "1"));
		}
		else
			chdir(homedir->val);
	}
	else if (go_to(cmnd->next) == -1)
	{
		perror("cd");
		return (update_status(&env, "1"));
	}
	update_status(&env, "0");
	update_oldpwd(&env);
	update_pwd(&env);
}
