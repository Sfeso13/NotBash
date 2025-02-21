/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delone_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:49:08 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 18:52:01 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	delone_shell(t_shell **head, t_shell *lst, void (*del)(void*))
{
	t_shell *prev;
	t_shell	*next;

	if (lst && del)
	{
		if (lst->args)
			free_tab(lst->args);
		if (lst->heredoc_dlm)
			free(lst->heredoc_dlm);
		if (lst->infile)
			free(lst->infile);
		if (lst->outfile)
			free(lst->outfile);
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
