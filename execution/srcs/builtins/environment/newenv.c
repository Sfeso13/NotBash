/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:26:44 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 12:32:56 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

t_env	*newenv(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = ft_strdup(key);
	node->val = ft_strdup(value);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
