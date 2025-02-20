/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:05:56 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/19 18:39:29 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

// t_shell	*inparse(char *input)
// {
// 	t_shell	*cmd = NULL;
// 	t_shell	*newcmd;
// 	char	**tokens;
// 	int		i;

// 	if (!input || !*input)
// 		return (NULL);
// 	if (advsyncatcher(input) == 1)
// 		return (NULL);
// 	i = 0;
// 	tokens = tokenizer(input);
// 	if (!tokens || !*tokens[i])
// 		return (NULL);
// 	while (tokens[i])
// 	{
// 		while (tokens[i] && is_pipe(tokens[i]))
// 			i++;
// 		if (!tokens)
// 			break ;
// 		newcmd = cmd_create();
// 		if (!newcmd)
// 		{
// 			free_double(tokens);
// 			return (NULL);
// 		}
// 		if (!tokenpars(&i, tokens, newcmd))
// 		{
// 			free_cmd(newcmd);
// 			free_double(tokens);
// 			return (NULL);
// 		}
// 		if (newcmd->args && newcmd->args[0])
// 			newcmd->is_buiultin = isbuiltincomm(newcmd->args[0]);
// 		expantions(newcmd);
// 		cmd_add(&cmd, newcmd);
// 	}
// 	free_double(tokens);
// 	return (cmd);
// }
