/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:08:53 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/03 23:38:22 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	update_status(t_env **env, char *status)
{
	t_env	*node;

	node = search_key("?", *env);
	if (!node)
		envadd_back(env, newenv("?", status));
	else
		set_env_value(&node, ft_strdup(status));
}
