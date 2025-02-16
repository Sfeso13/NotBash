/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 13:22:21 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	which_builtin(char *cmnd, t_env *env)
{
	if (improved_cmp(cmnd, "env"))
		print_env(env);
	printf("other builtins\n-----------------------\n");
}

void	execute(t_shell *cmnds, t_env *env)
{
    if (is_builtin(cmnds->args[0]))
		which_builtin(cmnds->args[0], env);
}