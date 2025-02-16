/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:44:23 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 19:07:40 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	quoting_check(char *input)
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
