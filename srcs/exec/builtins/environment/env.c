/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:16 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 10:56:59 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->val && env->key[0] != '.')
			printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}
