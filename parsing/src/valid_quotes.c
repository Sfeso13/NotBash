/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:44:23 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/13 20:08:02 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
