/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:03:33 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:27:45 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/helpers.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmps;

	tmps = (unsigned char *)s;
	while (n > 0)
	{
		*tmps = 0;
		tmps++;
		n--;
	}
}
