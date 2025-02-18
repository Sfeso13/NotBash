/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:50:06 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/18 17:10:15 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int emptychecker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int displaymeagn(char **input)
{
	if (!input || !*input || *input == (void *)0 || emptychecker(*input))
	{
		free(*input);
		*input = NULL;
		return (1);
	}
	return (0);
}
