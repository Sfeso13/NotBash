/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:45 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/14 23:59:29 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenpars(int *i, char **tokens, t_shell *cmd)
{
	if (!tokens || !*tokens || !tokens[*i] || !**tokens)
		return (0);
	while (tokens[*i])
	{
		if (is_redirection(tokens[*i]))
		{
			if (!redir_isgood(i, tokens, cmd))
				return (0); // syn error
			continue ;
		}
		else if (is_pipe(tokens[*i]))
		{
			if (!pipe_isgood(cmd))
				return (0);
		}
		else if (nonvalidtoken(tokens[*i]))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", tokens[*i]);
			return (0);
		}
		else
		{
			if (!arg_isgood(i, tokens, cmd))
				return (0);
		}
		(*i)++;
	}
	return (1);
}
