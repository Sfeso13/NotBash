/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:16 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/03 15:04:11 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key && tmp->val && tmp->is_set == 1)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	update_status(env, "0");
}
