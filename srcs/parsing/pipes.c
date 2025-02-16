/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:07:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:19:48 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/minishell.h"

int	is_pipe(char *token)
{
	return (ft_strncmp(token, "|", 1) == 0);
}

int	checkpipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
		{
			if (i == 0 || !tokens[i + 1] || is_pipe(tokens[i + 1]))
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	emptycomm(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) && (!tokens[i + 1] || is_pipe(tokens[i + 1])))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		i++;
	}
	return (1);
}
