/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:29:02 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/23 17:56:01 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static int	can_tilde(t_expander *exp)
{
	const char	next_char = exp->value[exp->i + 1];

	return (!exp->in_single && !exp->in_double
		&& (exp->buf_pos == 0 || exp->buffer[exp->buf_pos - 1] == ':')
		&& (next_char == '/' || next_char == '\0'));
}

static void	expand_tilde(t_expander *exp)
{
	char	*home;

	home = get_env_value("HOME", exp->env);
	if (home)
		append_str(exp, home);
	else
		append_char(exp, '~');
	exp->i++;
}

static void	char_process(t_expander *exp)
{
	char	c;

	c = exp->value[exp->i];
	if (exp->escape_next)
	{
		append_char(exp, c);
		exp->escape_next = 0;
		exp->i++;
	}
	else if (c == '\\')
		handle_backslash(exp);
	else if (c == '\'' || c == '"')
		handle_quote(exp, c);
	else if (c == '$' && !exp->in_single)
		expand_var(exp);
	else if (c == '~' && can_tilde(exp))
		expand_tilde(exp);
	else
		append_char(exp, exp->value[exp->i++]);
}

char	*expand_token(char *value, t_env *env)
{
	t_expander	exp;

	init_expander(&exp, value, env);
	while (exp.value[exp.i])
		char_process(&exp);
	return (exp.buffer);
}

void	analyze_in_expand(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*or_val;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			or_val = current->value;
			current->value = expand_token(or_val, env);
			free(or_val);
		}
		current = current->next;
	}
}
