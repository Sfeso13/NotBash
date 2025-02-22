/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:24:12 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/22 18:04:28 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	append_char(t_expander *exp, char c)
{
	if (exp->buf_pos + 1 >= exp->buf_size)
	{
		exp->buf_size *= 2;
		exp->buffer = ft_realloc(exp->buffer, exp->buf_size / 2, exp->buf_size);
	}
	exp->buffer[exp->buf_pos++] = c;
	exp->buffer[exp->buf_pos] = '\0';
}

void	append_str(t_expander *exp, char *str)
{
	while (str && *str)
		append_char(exp, *str++);
}

void	handle_backslash(t_expander *exp)
{
	exp->i++;
	if (exp->in_single)
		append_char(exp, '\\');
	else if (exp->in_double)
	{
		if (ft_strchr("$\"`\\\n", exp->value[exp->i]))
		{
			if (exp->value[exp->i])
				append_char(exp, exp->value[exp->i++]);
		}
		else
			append_char(exp, '\\');
	}
	else
	{
		if (exp->value[exp->i])
			append_char(exp, exp->value[exp->i++]);
		else
			append_char(exp, '\\');
	}
}

void	handle_quote(t_expander *exp, char quote)
{
	if (quote == '\'' && !exp->in_double)
		exp->in_single = !exp->in_single;
	else if (quote == '"' && !exp->in_single)
		exp->in_double = !exp->in_double;
	else
		append_char(exp, quote);
	exp->i++;
}

void	expand_var(t_expander *exp)
{
	size_t	start;
	char	*var_name;
	char	*var_val;

	exp->i++;
	start = exp->i;
	while (ft_isalnum(exp->value[exp->i]) || exp->value[exp->i] == '_' || \
		   exp->value[exp->i] == '?')
		exp->i++;
	if (start == exp->i)
		return (append_char(exp, '$'));
	var_name = ft_substr(exp->value, start, exp->i - start);
	var_val = get_env_value(var_name, exp->env);
	if (var_val)
		append_str(exp, var_val);
	free(var_name);
}
