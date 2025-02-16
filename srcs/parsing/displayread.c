/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:50:06 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:19:28 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/minishell.h"

char	*displayread(t_shell *cmd)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		cmd = inparse(input);
		if (!cmd)
		{
			free(input);
			continue;
		}
		printme(cmd);
		free(input);
		free_cmd(cmd);
	}
}
