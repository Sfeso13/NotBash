/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:07:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/13 21:01:40 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char *token)
{
	return (ft_strncmp(token, "|", 1) == 0);
}

int	pipe_isgood(t_shell *cmd)
{
	t_shell	*newcmd;

	newcmd = cmd_create();
	if (!newcmd)
		return (0);
	cmd->next = newcmd;
	newcmd->prev = cmd;
	return (1);
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
