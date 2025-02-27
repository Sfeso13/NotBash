/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_helptw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:50:18 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/27 20:02:09 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static void	free_split_values(char **split_values)
{
	int	i;

	i = 0;
	while (split_values[i])
	{
		free(split_values[i]);
		i++;
	}
	free(split_values);
}

static t_token	*create_new_token(char *value, t_token *prev)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = TOKEN_WORD;
	new_token->value = ft_strdup(value);
	new_token->prev = prev;
	new_token->next = prev->next;
	if (prev->next)
		prev->next->prev = new_token;
	prev->next = new_token;
	return (new_token);
}

static void	insert_new_tokens(t_token *current, char **split_values)
{
	t_token	*prev;
	t_token	*new_token;
	int		i;

	prev = current;
	i = 1;
	while (split_values[i])
	{
		new_token = create_new_token(split_values[i], prev);
		if (!new_token)
			break ;
		prev = new_token;
		i++;
	}
}

void	split_and_insert(t_token *current)
{
	char	**split_values;

	split_values = ft_old_split(current->value, '\x01');
	if (!split_values || !split_values[0])
		return ;
	free(current->value);
	current->value = ft_strdup(split_values[0]);
	insert_new_tokens(current, split_values);
	free_split_values(split_values);
}
