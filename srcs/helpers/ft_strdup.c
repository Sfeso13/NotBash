/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:37:09 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:28:14 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/helpers.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		slen;
	int		i;

	i = 0;
	slen = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * slen + 1);
	if (!str)
		return (NULL);
	while (i < slen)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
