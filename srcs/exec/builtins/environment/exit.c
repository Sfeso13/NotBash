/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:34:19 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/21 19:37:50 by yhossni          ###   ########.fr       */
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

void    exit_shell(t_shell **cmnds, t_env **env)
{
	if (arr_len((*cmnds)->args) > 2)
	{
		printf("exit\n");
		printf("exit : too many arguments\n");
	}
    else if (arr_len((*cmnds)->args) == 1)
    {
		printf("exit\n");
		if (*env)
			clear_env(env, free);
		if (*cmnds)
			clear_env(env, free);
		exit(0);
	}
	else
	{
		if (!validate_status((*cmnds)->args[1]))
		{
			printf("exit: %s: numeric argument required\n", (*cmnds)->args[1]);
			if (*env)
				clear_env(env, free);
			if (*cmnds)
				clear_env(env, free);
			exit(255);
		}
		exit(ft_atoi((*cmnds)->args[1]));
	}
}
