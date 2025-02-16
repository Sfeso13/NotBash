/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:29:02 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:19:31 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/minishell.h"

void	expantions(t_shell *cmd)
{
	char	*expaded;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		expaded = expand_it(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = expaded;
		i++;
	}
}
char	*expand_it(char *token)
{
	char	*name_var;
	char	*value_var;
	// char	*home_dir;
	// char	*exit_stat;

	// if (ft_strncmp(token, "$?", 2) == 0)
	// {
	// 	exit_stat = ft_itoa wla perror(exit stats);
	// 	return (exit stat);
	// }
	if (token[0] == '$')
	{
		name_var = token + 1;
		value_var = getenv(name_var);
		if (value_var)
			return (ft_strdup(value_var));
		else
			return (ft_strdup(""));
	}
	// if (token[0] == '~')
	// {
	// 	home_dir = getenv("HOME");
	// 	if (home_dir)
	// 	{
	// 		if (token[1])
	// 			return (ft_strdup(home_dir));
	// 		else
	// 			return (ft_strjoin(home_dir, token + 1));
	// 	}
	// }
	return (ft_strdup(token));
}
