/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:36:31 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/28 21:32:02 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	allowed(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') || \
			c[i] == '_' || (c[i] >= '0' && c[i] <= '9') || c[i] == '+' || \
			c[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	is_plus(char *s)
{
	int		i;
	int		count;
	char	*plus;

	i = 0;
	count = 0;
	plus = NULL;
	while (s[i])
	{
		if (s[i] == '+')
			count++;
		i++;
	}
	if (count > 0)
		plus = ft_strchr(s, '+');
	if (plus && count == 1)
	{
		if (*(plus + 1) != '=')
			return (-1);
	}
	return (count);
}

char	*key_error(char *key)
{
	free(key);
	return (NULL);
}

char	*validate_key(char *key)
{
	int		plus;
	size_t	len;
	char	*res;

	if (!allowed(key))
		return (key_error(key));
	len = ft_strlen(key);
	plus = is_plus(key);
	if (plus > 1 || plus == -1)
		return (key_error(key));
	else if ((plus && (key[len - 2] != '+')) || \
		(key[0] >= '0' && key[0] <= '9'))
		return (key_error(key));
	res = ft_strtrim(key, "+=");
	free(key);
	return (res);
}
