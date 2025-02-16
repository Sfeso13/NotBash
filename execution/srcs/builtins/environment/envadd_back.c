/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:22:13 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 11:35:57 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst && new)
	{
		tmp = findlast_env(*lst);
		if (!tmp)
		{
			*lst = new;
			return ;
		}
		tmp->next = new;
		new->prev = tmp;
	}
}
