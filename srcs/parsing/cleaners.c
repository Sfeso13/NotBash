/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:24:37 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 19:06:58 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	free_cmd(t_shell *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->heredoc_dlm);
	free(cmd);
}

void	free_double(char **dbl)
{
	int	i;

	i = 0;
	if (!*dbl || !dbl)
		return ;
	while (dbl[i])
		free(dbl[i++]);
	free(dbl);
}

void	freewords(char **res, int i)
{
	while (i--)
	{
		write(1, "7\n", 2);
		free(res[i]);
	}
	free(res);
}
