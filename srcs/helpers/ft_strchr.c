/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:21:36 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 11:21:37 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	p;

	p = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == p)
			break ;
		i++;
	}
	if (s[i] == p)
		return ((char *)(s + i));
	return (NULL);
}
