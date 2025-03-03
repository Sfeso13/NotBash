/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:05:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/03 00:06:17 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	count_words(char const *str)
{
	int	i;
	int	cword;
	int	count;

	i = 0;
	cword = 0;
	count = 0;
	while (str[i])
	{
		if (iswhitespace(str[i]))
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
