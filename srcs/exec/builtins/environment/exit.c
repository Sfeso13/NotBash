/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:34:19 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 13:12:38 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	validate_status(char *status)
{
	int	i;

	i = 0;
	while (status[i])
	{
		if (!ft_isdigit(status[i]) && (status[i] != '-' && status[i] != '+'))
			return (0);
		i++;
	}
	return (1);
}

void	clear_structs(t_shell **shell, t_env **env)
{
	if (*env)
		clear_env(env, free);
	if (*shell)
		clear_shell(shell, free);
}

void	exit_shell(t_shell **shell, t_token **cmnd, t_env **env)
{
	if (how_many_args(*cmnd, TOKEN_WORD) > 2)
	{
		printf("exit\n");
		printf("exit : too many arguments\n");
	}
	else if (how_many_args(*cmnd, TOKEN_WORD) == 1)
	{
		printf("exit\n");
		clear_structs(shell, env);
		exit(0);
	}
	else
	{
		if (!validate_status((*cmnd)->next->value))
		{
			printf("exit: %s: numeric argument required\n", \
			(*cmnd)->next->value);
			clear_structs(shell, env);
			exit(255);
		}
		exit(ft_atoi((*cmnd)->next->value));
	}
}
