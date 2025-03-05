/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:54:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/05 15:19:07 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	err(char *value, int *status)
{
	ft_putstr_fd("invalid id :", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("\n", 2);
	*status = 1;
}

int	internal_vars(t_env *env)
{
	if (improved_cmp("PWD", env->key) == 0 || \
		improved_cmp("OLDPWD", env->key) == 0)
		return (1);
	return (0);
}

void	save_vars(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	if (!search_key(".pwd", *env))
		envadd_back(env, newenv(".pwd", NULL, 0));
	if (!search_key(".oldpwd", *env))
		envadd_back(env, newenv(".oldpwd", NULL, 0));
	pwd = search_key(".pwd", *env);
	oldpwd = search_key(".oldpwd", *env);
	pwd->val = ft_strdup(search_key("PWD", *env)->val);
	oldpwd->val = ft_strdup(search_key("OLDPWD", *env)->val);
}

void	check_isset(t_token *cmnd, t_env **env)
{
	t_env	*to_remove;

	to_remove = search_key(cmnd->value, *env);
	printf("attempting to remove : %s\n", to_remove->key);
	if (to_remove && to_remove->is_set && internal_vars(to_remove))
	{
		save_vars(env);
		set_env_value(&to_remove, NULL);
		to_remove->is_set = 0;
	}
	else if (to_remove && (improved_cmp(to_remove->key, "PATH") == 0 \
			|| to_remove->is_set))
	{
		printf("deleting\n");
		delone_env(env, to_remove, free);
	}
}

void	unset_var(t_token *cmnd, t_env **env)
{
	int		status;

	status = 0;
	if (how_many_args(cmnd) > 1)
	{
		cmnd = cmnd->next;
		while (cmnd && cmnd->type == TOKEN_WORD)
		{
			if (!unset_validate_key(cmnd->value))
			{
				err(cmnd->value, &status);
				cmnd = cmnd->next;
				continue ;
			}
			check_isset(cmnd, env);
			cmnd = cmnd->next;
		}
	}
	if (status == 0)
		return (update_status(env, "0"));
	return (update_status(env, "1"));
}
