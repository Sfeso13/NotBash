/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:16 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 16:36:50 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

/*  used by the 'env' command   */

char	**builtins(void)
{
	static char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}

int	is_builtin(char *cmnd)
{
	char	**builtin_cmnds;
	int		i;

	i = 0;
	builtin_cmnds = builtins();
	while (builtin_cmnds[i])
	{
		if (improved_cmp(cmnd, builtin_cmnds[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}
