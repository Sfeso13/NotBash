/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:47:32 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/28 16:47:33 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	init_expander(t_expander *exp, char *value, t_env *env, int inexp)
{
	exp->value = value;
	exp->i = 0;
	exp->buf_size = 128;
	exp->buffer = ft_calloc(exp->buf_size, sizeof(char));
	exp->buf_pos = 0;
	exp->env = env;
	exp->in_single = 0;
	exp->in_double = 0;
	exp->escape_next = 0;
	exp->expme = inexp;
}
