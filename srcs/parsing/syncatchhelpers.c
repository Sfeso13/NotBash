/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncatchhelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:44:23 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 00:10:52 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	quoting_check(const char *input)
{
	int	onequ;
	int	dblqu;

	onequ = 0;
	dblqu = 0;
	while (*input)
	{
		if (*input == '\'' && !dblqu)
			onequ = !onequ;
		else if (*input == '"' && !onequ)
			dblqu = !dblqu;
		input++;
	}
	return (onequ || dblqu);
}

int	invalids(const char **token)
{
	const char	*st;

	st = *token;
	(*token)++;
	if (*st == **token)
		(*token)++;
	while (**token == ' ' || **token == '\t')
		(*token)++;
	if (**token == '\0' || **token == '>' || **token == '<' || **token == '|')
		return (1);
	return (0);
}

int	redir_check(const char *token)
{
	int	scc;
	int	dcc;

	scc = 0;
	dcc = 0;
	while (*token)
	{
		if (*token == '\'')
			scc++;
		else if (*token == '"')
			dcc++;
		if ((!(scc % 2) && !(dcc % 2)) && (*token == '>' || *token == '<'))
		{
			if (invalids(&token))
				return (1);
		}
		else
			token++;
	}
	return (0);
}

int	notsupported(const char *token)
{
	int	scc;
	int	dcc;

	scc = 0;
	dcc = 0;
	while (*token)
	{
		if (*token == '\'')
			scc++;
		else if (*token == '"')
			dcc++;
		if (!(scc % 2) && !(dcc % 2))
		{
			if ((*token == '&' && *(token + 1) == '&')
				|| (*token == '|' && *(token + 1) == '|'))
				return (1);
		}
		token++;
	}
	return (0);
}
