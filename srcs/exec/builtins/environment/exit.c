/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:34:19 by yhossni           #+#    #+#             */
/*   Updated: 2025/05/05 18:33:06 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	validate_status(char *status)
{
	int			i;
	int			m_count;
	int			p_count;
	long long	stat;

	i = 0;
	m_count = 0;
	p_count = 0;
	while (status[i])
	{
		if (!ft_isdigit(status[i]) && (status[i] != '-' && status[i] != '+'))
			return (0);
		if (status[i] == '-')
			m_count++;
		if (status[i] == '+')
			p_count++;
		i++;
	}
	if ((m_count && p_count) || (m_count > 1 || p_count > 1))
		return (0);
	stat = ft_atoi(status);
	if (errno == ERANGE)
		return (0);
	return (1);
}

void	clear_structs(t_shell **shell, t_env **env)
{
	if (*env)
		clear_env(env, free);
	if (*shell)
		clear_shell(shell, free);
}

void	p_exit_err(char *exit, char *val, char *msg)
{
	if (exit)
		ft_putstr_fd(exit, 2);
	ft_putstr_fd("exit: ", 2);
	if (val)
		ft_putstr_fd(val, 2);
	if (msg)
		ft_putstr_fd(msg, 2);
}

int	get_last_status(t_shell *shell, t_env *env)
{
	t_env	*stat_node;

	if (shell->prev)
		return (0);
	ft_putstr_fd("exit\n", 1);
	stat_node = search_key("?", env);
	if (stat_node && stat_node->val)
		return (ft_atoi(stat_node->val));
	else
		return (0);
}

void	exit_shell(t_shell **shell, t_token **cmnd, t_env **env)
{
	int	s;

	if ((*cmnd)->next && !validate_status((*cmnd)->next->value))
	{
		p_exit_err("exit\n", (*cmnd)->next->value, \
		": numeric argument required\n");
		clear_structs(shell, env);
		exit(255);
	}
	else if (how_many_args(*cmnd) > 2)
	{
		p_exit_err("exit\n", NULL, "exit : too many arguments\n");
		update_status(env, "1");
	}
	else if (how_many_args(*cmnd) == 1)
	{
		s = get_last_status(*shell , *env);
		clear_structs(shell, env);
		exit (s);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi((*cmnd)->next->value));
	}
}
