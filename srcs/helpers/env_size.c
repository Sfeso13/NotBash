/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:40:22 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 11:03:17 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	env_size(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (lst->key[0] != '.')
			count++;
		lst = lst->next;
	}
	return (count);
}
