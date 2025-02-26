/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:36:31 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 15:36:41 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	unset_allowed(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') || \
			c[i] == '_' || (c[i] >= '0' && c[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

char	*unset_validate_key(char *key)
{
	int		i;
	size_t	len;

	i = 0;
	if (!unset_allowed(key))
		return (NULL);
	len = ft_strlen(key);
	if ((key[0] >= '0' && key[0] <= '9') || key[0] == '\0')
		return (NULL);
	return (key);
}
