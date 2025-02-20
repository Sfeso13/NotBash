/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:23:51 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/19 17:48:09 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

char	*extract_token(char **input, int *scc, int *dcc)
{
	char	*st;
	char	quchar;
	int		len;
	int		in_quotes;

	len = 0;
	in_quotes = 0;
	quchar = 0;
	while (**input && iswhitespace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	if ((**input == '|' || **input == '<' || **input == '>' || **input == '&') && !(*scc % 2) && !(*dcc % 2))
	{
		st = *input;
		if ((**input == '>' && (*input)[1] == '>') || (**input == '<' && (*input)[1] == '<'))
		{
			if (!(*input)[1])
				return (NULL);
			*input += 2;
			return (ft_strndup(st, 2));
		}
		else
		{
			(*input)++;
			return (ft_strndup(st, 1));
		}
	}
	st = *input;
	while (**input)
	{
		if (!in_quotes)
		{
			if ((iswhitespace(**input) || ft_strchr("|<>", **input)) && !(*scc % 2) && !(*dcc % 2))
				break ;
			if (**input == '\'' || **input == '"')
			{
				in_quotes = 1;
				quchar = **input;
				if (quchar == '\'')
					(*scc)++;
				else
					(*dcc)++;
			}
		}
		else
		{
			if (**input == quchar)
			{
				in_quotes = 0;
				if (quchar == '\'')
					(*scc)++;
				else
					(*dcc)++;
			}
		}
		(*input)++;
		len++;
	}
	return (ft_strndup(st, len));
}
t_token_type	get_token_type(const char *str)
{
	const char			*ops[] = {"|", "<", ">", ">>", "<<", NULL};
	const t_token_type	types[] = {TOKEN_PIPE, TOKEN_REDIRECT_IN, TOKEN_REDIRECT_OUT, TOKEN_APPEND, TOKEN_HEREDOC};
	int					i;

	i = 0;
	while (ops[i])
	{
		if (!ft_strcmp(str, ops[i]))
			return (types[i]);
		i++;
	}
	return TOKEN_WORD;
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new;
	char	*val;
	int		scc;
	int		dcc;

	head = NULL;
	tail = NULL;
	scc = 0;
	dcc = 0;
	while (*input)
	{
		while (iswhitespace(*input))
			input++;
		if (!*input)
			break ;
		val = extract_token(&input, &scc, &dcc);
		if (!val)
			break ;
		new = malloc(sizeof(t_token));
		if (!new)
		{
			free(val);
			break ;
		}
		new->value = val;
		new->type = get_token_type(val);
		new->next = NULL;
		if (!head)
			head = tail = new;
		else
			tail = tail->next = new;
	}
	return (head);
}
