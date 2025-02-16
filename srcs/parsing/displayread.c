/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:50:06 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 19:07:05 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

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
