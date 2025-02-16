/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:05:56 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:19:45 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/minishell.h"

t_shell	*inparse(char *input)
{
	t_shell	*cmd = NULL;
	t_shell	*newcmd;
	char	**tokens;
	int		i;

	if (!input || !*input)
		return (NULL);
	i = 0;
	tokens = tokenizer(input);
	if (!tokens || !*tokens[i])
		return (NULL);
	if (!checkpipes(tokens) || !emptycomm(tokens))
	{
		free_double(tokens);
		return (NULL);
	}
	while (tokens[i])
	{
		while (tokens[i] && is_pipe(tokens[i]))
			i++;
		if (!tokens)
			break ;
		newcmd = cmd_create();
		if (!newcmd)
		{
			free_double(tokens);
			return (NULL);
		}
		if (!tokenpars(&i, tokens, newcmd))
		{
			free_cmd(newcmd);
			free_double(tokens);
			return (NULL);
		}
		expantions(newcmd);
		cmd_add(&cmd, newcmd);
	}
	free_double(tokens);
	return (cmd);
}
