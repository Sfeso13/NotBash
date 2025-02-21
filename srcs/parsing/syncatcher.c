/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:18:29 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 01:41:51 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	checkmy_syn(const char *input)
{
	if (quoting_check(input))
	{
		// ft_putstr_fd("Error unclosed quotes\n", 2);
		printf("Error unclosed quotes\n");
		return (1);
	}
	if (redir_check(input))
	{
		// ft_putstr_fd("Error invalid redirections\n", 2);
		printf("Error invalid redirections\n");
		return (1);
	}
	if (itsmisplaced(input))
	{
		// ft_putstr_fd("Error misplaced OP\n", 2);
		printf("Error misplaced OP\n");
		return (1);
	}
	if (notsupported(input))
	{
		// ft_putstr_fd("Error theres a non supported OP\n", 2);
		printf("Error a non supported OP\n");
		return (1);
	}
	return (0);
}

int	advsyncatcher(char *input)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, " \f\v\t\n\r");
	if (!trimmed)
		return (1);
	if (checkmy_syn(trimmed))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}
