/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fillhelp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:44:45 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/09 00:30:27 by adechaji         ###   ########.fr       */
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
	new->expanded = src->expanded;
	new->ambiguous = src->ambiguous;
	new->ignore = src->ignore;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*cpy_till_pipe(t_token **curr)
{
	t_token	*head;
	t_token	**dst;
	t_token	*new_token;
	t_token	*prev_cpy;

	head = NULL;
	dst = &head;
	prev_cpy = NULL;
	while (*curr && (*curr)->type != TOKEN_PIPE)
	{
		if ((*curr)->ignore == 1)
		{
			*curr = (*curr)->next;
			continue ;
		}
		new_token = copy_token(*curr);
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		new_token->prev = prev_cpy;
		*dst = new_token;
		prev_cpy = new_token;
		dst = &(*dst)->next;
		*curr = (*curr)->next;
	}
	return (head);
}
