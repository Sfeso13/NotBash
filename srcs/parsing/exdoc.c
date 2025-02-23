/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exdoc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:36:00 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 20:20:14 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static char	*extract_value(char *str, int *i, t_env *env)
{
	char	*key;
	int		start;
	int		len;

	(*i)++;
	start = *i;
	if (str[*i] == '{')
	{
		start = ++(*i);
		while (str[*i] && str[*i] != '}')
			(*i)++;
		len = (*i)++ - start;
	}
	else
	{
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		len = *i - start;
	}
	key = ft_substr(str, start, len);
	return (get_env_value(key, env));
}

char	*expanddoc(char *str, t_env *env)
{
	char	*result;
	char	*value;
	int		i[3];

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	result = malloc(ft_strlen(str) * 2 + 1);
	if (!result)
		return (NULL);
	while (str[++i[0]])
	{
		if (str[i[0]] == '$' && (i[0] == 0 || str[i[0] - 1] != '\\'))
		{
			value = extract_value(str, &i[0], env);
			if (value)
			{
				ft_strlcpy(&result[i[1]], value, ft_strlen(value) + 1);
				i[1] += ft_strlen(value);
				free(value);
			}
		}
		else
			result[i[1]++] = str[i[0]];
	}
	result[i[1]] = '\0';
	return (result);
}
