/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:07:03 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:19:51 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/minishell.h"

int	is_redirection(char *token)
{
	if (!token || !*token)
		return (0);
	return (ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, ">", 1) == 0 ||
		ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0);

}

int	redir_isgood(int *i, char **tokens, t_shell *cmd)
{
	char	*type;

	if (!tokens || !*tokens || !tokens[*i])
		return (0);
	type = tokens[*i];
	(*i)++;
	if (!tokens[*i])
	{
		printf("minishell: syntax error near unexpected token `%s'\n", tokens[*i] ? tokens[*i] : "\'\n'");
		return (0);
	}
	if (ft_strncmp(type, ">>", 2) == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(tokens[*i]);
		cmd->append_mode = 1;
	}
	else if (ft_strncmp(type, "<<", 2) == 0)
	{
		if (cmd->heredoc_dlm)
			free(cmd->heredoc_dlm);
		cmd->heredoc_dlm = ft_strdup(tokens[*i]);
	}
	else if (ft_strncmp(type, "<", 1) == 0)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(tokens[*i]);
	}
	else if (ft_strncmp(type, ">", 1) == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(tokens[*i]);
	}
	return (1);
}
