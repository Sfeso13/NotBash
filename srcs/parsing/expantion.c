/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:29:02 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/22 15:18:37 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	can_tilde(t_expander *exp)
{
	const char	next_char = exp->value[exp->i + 1];

	return (!exp->in_single && !exp->in_double
		&& (exp->buf_pos == 0 || exp->buffer[exp->buf_pos - 1] == ':')
		&& (next_char == '/' || next_char == '\0'));
}

void	expand_tilde(t_expander *exp)
{
	char	*home;

	home = get_env_value("HOME", exp->env);
	if (home)
		append_str(exp, home);
	else
		append_char(exp, '~');
	exp->i++;
}

t_expander	expand_token(char *value, t_env *env, int inexp, int after_pipe)
{
	t_expander	exp;

	init_expander(&exp, value, env, inexp);
	exp.aft_pipe = after_pipe;
	while (exp.value[exp.i])
		char_process(&exp);
	return (exp);
}

static void	proc_token_exp(t_token *current, t_env *env)
{
	static int	inexp;
	static int	dol;

	dol = 0;
	inexp = 0;
	chinexpdola(current, &inexp, &dol);
	if (current->type == TOKEN_WORD
		&& (!current->prev || current->prev->type != TOKEN_HEREDOC))
	{
		if (current->expanded == 0)
			expprocetoken(current, env, inexp, dol);
	}
}

int	analyze_in_expand(t_token *tokens, t_env *env)
{
	t_token	*current;
	int		after_pipe;

	current = tokens;
	after_pipe = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			after_pipe = 1;
		else
			current->after_pipe = after_pipe;
		current = current->next;
	}
	current = tokens;
	while (current)
	{
		proc_token_exp(current, env);
		current = current->next;
	}
	return (0);
}
