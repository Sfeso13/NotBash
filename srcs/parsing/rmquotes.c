/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:44:01 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/25 14:05:38 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	quotes_remove(t_token *token)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!token->value)
		return ;
	len = ft_strlen(token->value);
	res = malloc(len + 1);
	i = 0;
	j = 0;
	while (token->value[i])
	{
		if (token->value[i] != '\"')
			res[j++] = token->value[i];
		i++;
	}
	res[j] = '\0';
	free(token->value);
	token->value = res;
}

static void	handle_quotes(char c, int *in_single, int *in_double, size_t *i)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
	(*i)++;
}

char	*remove_doc_qts(char *input)
{
	char	*result;
	size_t	i;
	size_t	j;
	int		in_single;
	int		in_double;

	if (!input)
		return (NULL);
	result = ft_calloc(ft_strlen(input) + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if ((input[i] == '\'' && !in_double) || (input[i] == '"' && !in_single))
			handle_quotes(input[i], &in_single, &in_double, &i);
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
