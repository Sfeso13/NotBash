/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:45:43 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 18:52:31 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	clear_shell(t_shell **lst, void (*del)(void*))
{
	t_shell	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			delone_shell(lst, *lst, del);
			*lst = tmp;
		}
		*lst = NULL;
	}
}
