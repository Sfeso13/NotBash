/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:41:24 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 23:45:13 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	t_env	*node;

	node = search_key(key, env);
	if (node)
		return (node->val);
	return (NULL);
}
