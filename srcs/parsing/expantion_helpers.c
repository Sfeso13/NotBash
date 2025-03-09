/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:24:12 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/09 17:10:21 by adechaji         ###   ########.fr       */
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

int	whitesonly(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!iswhitespace((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}


void	expand_var(t_expander *exp)
{
	size_t	start;
	char	*var_name;
	char	*var_val;
	int		i;
	char	**words;
	char	quote;
	char	*content;

	exp->i++;
	start = exp->i;
	if ((exp->value[exp->i] == '\'' || exp->value[exp->i] == '"')
		&& !exp->in_single && !exp->in_double)
	{
		quote = exp->value[exp->i];
		start = exp->i;
		while (exp->value[exp->i] && exp->value[exp->i] != quote)
			exp->i++;
		content = ft_substr(exp->value, start, exp->i - start);
		append_str(exp, content);
		free(content);
	}
	else if (ft_isdigit(exp->value[exp->i]))
	{
		while (ft_isdigit(exp->value[exp->i]))
			exp->i++;
		content = ft_substr(exp->value, start, exp->i - start);
		if (content && content[0] != '\0')
			append_str(exp, content + 1);
		free(content);
	}
	else
	{
		while (ft_isalnum(exp->value[exp->i]) || exp->value[exp->i] == '_' || \
				exp->value[exp->i] == '?')
			exp->i++;
		if (start == exp->i)
			return (append_char(exp, '$'));
		var_name = ft_substr(exp->value, start, exp->i - start);
		if (ft_strcmp(var_name, "?") == 0 && exp->aft_pipe)
			var_val = "0";
		else
			var_val = get_env_value(var_name, exp->env);
		if (var_val)
		{
			if (!exp->in_single && !exp->in_double && exp->expme == 0)
			{
				words = ft_split(var_val);
				i = 0;
				while (words[i])
				{
					append_str(exp, words[i]);
					if (words[i + 1])
						append_char(exp, '\x01');
					i++;
				}
				free_tab(words);
			}
			else
				append_str(exp, var_val);
		}
		if (whitesonly(exp->buffer) == 1)
				exp->ignoreme = 1;
		free(var_name);
	}
}
