/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delone_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:49:08 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/09 01:28:06 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	mid_del_token(t_token *prev, t_token *next, t_token *lst)
{
	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
}

void	delone_token(t_token **head, t_token *lst, void (*del)(void*))
{
	t_token	*prev;
	t_token	*next;

	if (lst && del)
	{
		if (lst->value)
			free(lst->value);
		if (lst->next && lst->prev)
			mid_del_token(prev = NULL, next = NULL, lst);
		else if (!lst->prev)
		{
			next = lst->next;
			if (next)
				next->prev = NULL;
			*head = next;
		}
		else if (!lst->next)
		{
			prev = lst->prev;
			if (prev)
				prev->next = NULL;
		}
		free(lst);
	}
}
