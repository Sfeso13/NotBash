/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:09:40 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 18:10:13 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

t_token	*search_token(t_token *token, t_token_type type)
{
	while (token)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}
