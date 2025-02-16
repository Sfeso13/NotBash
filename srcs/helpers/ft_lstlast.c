/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:55:03 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:28:03 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/helpers.h"

t_shell	*ft_lstlast(t_shell *lst)
{
	t_shell	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}