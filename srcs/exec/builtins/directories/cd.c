/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/20 09:50:56 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	update_pwd(t_env **env, char *path)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (improved_cmp(tmp->key, "PWD") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp->val)
		free(tmp->val);
	tmp->val = ft_strdup(path);
}

void	changedir(t_shell *cmnds, t_env *env)
{
	chdir(cmnds->args[1]);
	update_pwd(&env, cmnds->args[1]);
}
