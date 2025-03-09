/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delone_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:55:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/17 18:06:04 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	mid_del_env(t_env *prev, t_env *next, t_env *lst)
{
	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
}

void	clear_values(t_env *lst, void (*del)(void*))
{
	if (lst->key)
		del(lst->key);
	if (lst->val)
		del(lst->val);
}

void	delone_env(t_env **head, t_env *lst, void (*del)(void*))
{
	t_env	*prev;
	t_env	*next;

	prev = NULL;
	next = NULL;
	if (lst && del)
	{
		clear_values(lst, del);
		if (lst->next && lst->prev)
			mid_del_env(prev, next, lst);
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
