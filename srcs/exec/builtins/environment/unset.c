/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:54:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 19:34:56 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	unset_var(t_token *cmnd, t_env *env)
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
				printf("invalid id : %s\n", cmnd->value);
				status = 1;
				cmnd = cmnd->next;
				continue ;
			}
			to_remove = search_key(cmnd->value, env);
			if (to_remove)
				delone_env(&env, to_remove, free);
			cmnd = cmnd->next;
		}
	}
	if (status == 0)
		return (update_status(&env, "0"));
	return (update_status(&env, "1"));
}
