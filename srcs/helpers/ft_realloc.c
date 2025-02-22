/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:42:47 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/22 01:43:04 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!old_ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr && old_ptr)
	{
		ft_memcpy(new_ptr, old_ptr, old_size);
		free(old_ptr);
	}
	return (new_ptr);
}
