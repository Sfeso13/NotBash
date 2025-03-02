/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:54:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/01 16:39:28 by yhossni          ###   ########.fr       */
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

void	unset_var(t_token *cmnd, t_env **env)
{
	int		status;
	t_env	*to_remove;

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
			update_dash(cmnd, env);
			to_remove = search_key(cmnd->value, *env);
			if (to_remove)
				delone_env(env, to_remove, free);
			cmnd = cmnd->next;
		}
	}
	if (status == 0)
		return (update_status(env, "0"));
	return (update_status(env, "1"));
}
