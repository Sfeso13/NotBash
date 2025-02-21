/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_supported.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:46:25 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 01:41:27 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

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
