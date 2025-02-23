/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:23:51 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 17:56:55 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

char	*extract_token(char **input, int *scc, int *dcc)
{
	char				*st;
	t_quote_context		ctx;
	int					len;

	len = 0;
	ctx.state = (t_quote_state){0, 0};
	ctx.scc = scc;
	ctx.dcc = dcc;
	while (**input && iswhitespace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	if (ft_strchr("|<>", **input) && !(*scc % 2) && !(*dcc % 2))
		return (handle_operator(input));
	st = *input;
	while (**input)
	{
		process_char(input, &len, &ctx);
		if (!ctx.state.in_quotes
			&& (iswhitespace(**input) || ft_strchr("|<>", **input)))
			break ;
	}
	return (ft_strndup(st, len));
}

static void	add_token_to_list(t_token **head, t_token **tail, char *val)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(val);
		return ;
	}
	new->value = val;
	new->type = get_token_type(val);
	new->next = NULL;
	new->prev = *tail;
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	char	*val;
	t_quote	quotes;

	head = NULL;
	tail = NULL;
	quotes = (t_quote){0, 0};
	while (*input)
	{
		while (iswhitespace(*input))
			input++;
		if (!*input)
			break ;
		val = extract_token(&input, &quotes.scc, &quotes.dcc);
		if (!val)
			break ;
		add_token_to_list(&head, &tail, val);
	}
	return (head);
}
