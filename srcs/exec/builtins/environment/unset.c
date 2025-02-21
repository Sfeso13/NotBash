/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:54:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 13:23:26 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	unset_var(t_shell *cmnds, t_env *env)
{
	int		i;
	t_env	*to_remove;

	i = 1;
	if (arr_len(cmnds->args) == 1)
		return ;
	while (cmnds->args[i])
	{
		if (!unset_validate_key(ft_strdup(cmnds->args[i])))
		{
			printf("invalid id : %s\n", cmnds->args[i]);
			i++;
			continue ;
		}
		to_remove = search_key(cmnds->args[i], env);
		if (to_remove)
		{
			ft_lstdelone(&env, to_remove, free);
		}
		i++;
	}
}
