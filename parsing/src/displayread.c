/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:50:06 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/14 22:01:04 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
