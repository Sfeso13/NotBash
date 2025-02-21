/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fillhelp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:44:45 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 22:18:49 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

t_shell	*crt_node(void)
{
	t_shell	*node;

	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->tokens = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*copy_token(t_token *src)
{
	t_token	*new;

	if (!src)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(src->value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = src->type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

