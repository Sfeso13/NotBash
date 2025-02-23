/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:55:23 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 17:55:40 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

t_token_type	get_token_type(const char *str)
{
	const char			*ops[] = {"|", "<", ">", ">>", "<<", NULL};
	const t_token_type	types[] = {TOKEN_PIPE, TOKEN_REDIRECT_IN,
		TOKEN_REDIRECT_OUT, TOKEN_APPEND, TOKEN_HEREDOC};
	int					i;

	i = 0;
	while (ops[i])
	{
		if (!ft_strcmp(str, ops[i]))
			return (types[i]);
		i++;
	}
	return (TOKEN_WORD);
}

char	*handle_operator(char **input)
{
	char	*st;

	st = *input;
	if ((**input == '>' && (*input)[1] == '>')
		|| (**input == '<' && (*input)[1] == '<'))
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

void	process_quote_update(t_quote_context *ctx)
{
	if (ctx->state.quchar == '\'')
		(*ctx->scc)++;
	else
		(*ctx->dcc)++;
}

void	process_char(char **input, int *len, t_quote_context *ctx)
{
	if (!ctx->state.in_quotes)
	{
		if ((iswhitespace(**input) || ft_strchr("|<>", **input)))
			if (!(*ctx->scc % 2) && !(*ctx->dcc % 2))
				return ;
		if (**input == '\'' || **input == '"')
		{
			ctx->state.in_quotes = 1;
			ctx->state.quchar = **input;
			process_quote_update(ctx);
		}
	}
	else if (**input == ctx->state.quchar)
	{
		ctx->state.in_quotes = 0;
		process_quote_update(ctx);
	}
	(*input)++;
	(*len)++;
}
