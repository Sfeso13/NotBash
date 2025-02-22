/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:36:59 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/22 01:53:20 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static t_token	*cpy_till_pipe(t_token **curr)
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

t_shell	*fill_cmd(t_token *tokens)
{
	t_shell	*head;
	t_shell	*prev_shell;
	t_shell	*new_shell;
	t_token	*curr;
	t_token	*cpy_token;

	head = NULL;
	prev_shell = NULL;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE)
		{
			curr = curr->next;
			continue ;
		}
		new_shell = crt_node();
		if (!new_shell)
		{
			free_shell(head);
			return (NULL);
		}
		cpy_token = cpy_till_pipe(&curr);
		if (!cpy_token)
		{
			free(new_shell);
			free_shell(head);
			return (NULL);
		}
		new_shell->tokens = cpy_token;
		if (!head)
			head = new_shell;
		else
		{
			prev_shell->next = new_shell;
			new_shell->prev = prev_shell;
		}
		prev_shell = new_shell;
		if (curr && curr->type == TOKEN_PIPE)
			curr = curr->next;
	}
	return (head);
}
