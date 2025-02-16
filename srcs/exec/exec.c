/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 16:37:38 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	which_builtin(char *cmnd, t_env *env)
{
	if (improved_cmp(cmnd, "env") == 0)
		print_env(env);
	else
		printf("other builtins\n-----------------------\n");
}

void	execute(t_shell *cmnds, t_env *env)
{
    if (is_builtin(cmnds->args[0]))
		which_builtin(cmnds->args[0], env);
}
