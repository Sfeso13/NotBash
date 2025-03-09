/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delone_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:23:57 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/09 01:28:12 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	mid_del_shell(t_shell *prev, t_shell *next, t_shell *lst)
{
	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
}

void	delone_shell(t_shell **head, t_shell *lst, void (*del)(void*))
{
	t_shell	*prev;
	t_shell	*next;

	if (lst && del)
	{
		if (lst->tokens)
			clear_tokens(&lst->tokens, del);
		if (lst->next && lst->prev)
			mid_del_shell(prev = NULL, next = NULL, lst);
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
