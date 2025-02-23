/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misplacing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:18:27 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 00:10:28 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static void	update_quote_counts(char c, int *scc, int *dcc)
{
	if (c == '\'')
		(*scc)++;
	else if (c == '\"')
		(*dcc)++;
}

int	itsmisplaced(const char *token)
{
	int	flag;
	int	scc;
	int	dcc;

	flag = 0;
	scc = 0;
	dcc = 0;
	if (*token == '|')
		return (1);
	while (*token)
	{
		update_quote_counts(*token, &scc, &dcc);
		if ((*token == '|' || *token == '&') && (!(scc % 2) && !(dcc % 2)))
		{
			if (flag)
				return (1);
			flag = 1;
		}
		else if (!iswhitespace(*token))
			flag = 0;
		token++;
	}
	if (flag)
		return (1);
	return (0);
}
