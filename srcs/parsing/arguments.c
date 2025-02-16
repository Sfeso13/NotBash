/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:14:02 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 19:06:55 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	arg_isgood(int *i, char **tokens, t_shell *cmd)
{
	char	**newargs;
	int		len;
	int		j;

	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (0);
		cmd->args[0] = ft_strdup(tokens[*i]);
		cmd->args[1] = NULL;
	}
	else
	{
		len = 0;
		while (cmd->args[len])
			len++;
		newargs = malloc(sizeof(char *) * (len + 2));
		if (!newargs)
			return (0);
		j = 0;
		while (j < len)
		{
			newargs[j] = cmd->args[j];
			j++;
		}
		newargs[len] = ft_strdup(tokens[*i]);
		newargs[len + 1] = NULL;
		free(cmd->args);
		cmd->args = newargs;
	}
	return (1);
}
