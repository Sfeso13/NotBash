/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:55:10 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/17 18:06:04 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	ft_lstdelone(t_env **head, t_env *lst, void (*del)(void*))
{
	t_env	*prev;
	t_env	*next;

	if (lst && del)
	{
		if (lst->key)
			del(lst->key);
		if (lst->val)
			del(lst->val);
		if (lst->next && lst->prev)
		{
			prev = lst->prev;
			next = lst->next;
			prev->next = next;
			next->prev = prev;
		}
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
