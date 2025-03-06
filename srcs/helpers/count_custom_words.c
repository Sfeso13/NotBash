/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_custom_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:37:26 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/06 00:37:43 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	count_custom_words(char const *str)
{
	int	i;
	int	cword;
	int	count;

	i = 0;
	cword = 0;
	count = 0;
	while (str[i])
	{
		if (iswhitespace(str[i]) || str[i] == '\x01')
			cword = 0;
		else if (cword == 0)
		{
			count++;
			cword = 1;
		}
		i++;
	}
	return (count);
}
