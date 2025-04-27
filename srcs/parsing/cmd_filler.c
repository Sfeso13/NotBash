/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:36:59 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/27 15:20:28 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static void	link_nodes(t_shell **head, t_shell **prev_shell, t_shell *new_shell)
{
	if (!*head)
		*head = new_shell;
	else
	{
		(*prev_shell)->next = new_shell;
		new_shell->prev = *prev_shell;
	}
	*prev_shell = new_shell;
}

static t_token	*handle_token_copy(t_token **curr, t_shell *new_shell
								, t_shell *head)
{
	t_token	*cpy_token;

	cpy_token = cpy_till_pipe(curr);
	if (!cpy_token)
	{
		free(new_shell);
		free_shell(head);
	}
	return (cpy_token);
}

static t_shell	*create_shells(t_shell **head)
{
	t_shell	*new_shell;

	new_shell = crt_node();
	if (!new_shell)
		free_shell(*head);
	return (new_shell);
}

static int	process_cmd(t_token **curr, t_shell **head, t_shell	**prev_shell)
{
	t_shell	*new_shell;
	t_token	*cpy_token;

	new_shell = create_shells(head);
	if (!new_shell)
		return (0);
	cpy_token = handle_token_copy(curr, new_shell, *head);
	if (!cpy_token)
		return (0);
	new_shell->tokens = cpy_token;
	link_nodes(head, prev_shell, new_shell);
	if (*curr && (*curr)->type == TOKEN_PIPE)
		*curr = (*curr)->next;
	return (1);
}

t_shell	*fill_cmd(t_token *tokens)
{
	t_shell	*head;
	t_shell	*prev_shell;
	t_token	*curr;

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
		if (!process_cmd(&curr, &head, &prev_shell))
			return (NULL);
	}
	return (head);
}
