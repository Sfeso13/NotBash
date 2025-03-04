/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:18:29 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/03 17:04:59 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	checkmy_syn(const char *input, t_env *env)
{
	if (quoting_check(input))
	{
		ft_putstr_fd("Error unclosed quotes\n", 2);
		update_status(&env, "2");
		return (1);
	}
	if (redir_check(input))
	{
		ft_putstr_fd("Error invalid redirections\n", 2);
		update_status(&env, "2");
		return (1);
	}
	if (itsmisplaced(input))
	{
		ft_putstr_fd("Error misplaced OP\n", 2);
		update_status(&env, "2");
		return (1);
	}
	if (notsupported(input))
	{
		ft_putstr_fd("Error theres a non supported OP\n", 2);
		update_status(&env, "2");
		return (1);
	}
	return (0);
}

int	advsyncatcher(char *input, t_env **env)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, " \f\v\t\n\r");
	if (!trimmed)
		return (1);
	if (checkmy_syn(trimmed, *env))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}
