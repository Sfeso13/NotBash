/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findlast_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:11:48 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 11:32:46 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

t_env	*findlast_env(t_env *lst)
{
	while (lst)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
