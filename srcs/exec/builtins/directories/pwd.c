/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:36:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/03 23:00:31 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	print_current_dir(t_env *env)
{
	t_env	*node;

	node = search_key("PWD", env);
	if (!node->val)
		node = search_key(".pwd", env);
	printf("%s\n", node->val);
	update_status(&env, "0");
}
