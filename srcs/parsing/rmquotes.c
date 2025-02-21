/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:44:01 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 00:37:19 by adechaji         ###   ########.fr       */
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
		return (NULL);
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
