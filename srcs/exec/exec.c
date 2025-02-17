/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/17 16:45:37 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	which_builtin(t_shell *cmnds, t_env *env)
{
	if (improved_cmp(cmnds->args[0], "env") == 0)
		print_env(env);
	// else if (improved_cmp(cmnds->args[0], "export") == 0)
	// 	export_env(cmnds, env);
	else
		printf("other builtins\n");
}

void	execute(t_shell *cmnds, t_env *env)
{
    if (is_builtin(cmnds->args[0]))
		which_builtin(cmnds, env);
}
