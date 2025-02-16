/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:10:57 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:28:05 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/helpers.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t			i;
	unsigned char	*dst_data;
	unsigned char	*src_data;

	if (!src && !dest)
		return (NULL);
	i = 0;
	dst_data = (unsigned char *)dest;
	src_data = (unsigned char *)src;
	if (dst_data == src_data)
		return (dst_data);
	while (i < num)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	return (dst_data);
}
