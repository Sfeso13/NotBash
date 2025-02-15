/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:50:12 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/13 21:18:11 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*cmd_create(void)
{
	t_shell	*cmd;

	cmd = malloc(sizeof(t_shell));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append_mode = 0;
	cmd->heredoc_dlm = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	cmd_add(t_shell	**head, t_shell *newcmd)
{
	t_shell	*last;

	if (!*head)
	{
		*head = newcmd;
	}
	else
	{
		last = ft_lstlast(*head);
		last->next = newcmd;
		newcmd->prev = last;
	}
}
