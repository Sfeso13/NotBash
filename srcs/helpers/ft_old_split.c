/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_old_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:58:21 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/27 19:40:12 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static int	countwords(char const *str, char sep)
{
	int	i;
	int	cword;
	int	count;

	i = 0;
	cword = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == sep)
			cword = 0;
		else if (cword == 0)
		{
			count++;
			cword = 1;
		}
		i++;
	}
	return (count);
}

static int	wordlen(char const *str, char sep)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != sep)
		len++;
	return (len);
}

static void	free_old_words(char **res, int i)
{
	while (i--)
		free(res[i]);
	free(res);
}

static int	fillwords(char **res, const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = wordlen(s, c);
			res[i] = (char *)malloc(sizeof(char) * (len + 1));
			if (!res[i])
			{
				free_old_words(res, i);
				return (0);
			}
			ft_memcpy(res[i], s, len);
			res[i++][len] = '\0';
			s += len;
		}
	}
	res[i] = NULL;
	return (1);
}

char	**ft_old_split(char const *s, char c)
{
	int		cwords;
	char	**res;

	if (!s)
		return (NULL);
	cwords = countwords(s, c);
	res = (char **)malloc(sizeof(char *) * (cwords + 1));
	if (!res)
		return (NULL);
	if (!fillwords(res, s, c))
		return (NULL);
	return (res);
}
