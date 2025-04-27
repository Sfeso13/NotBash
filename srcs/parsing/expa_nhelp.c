/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_nhelp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:55:24 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/27 15:55:59 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	handle_norexp_quotes(t_expander *exp, size_t start)
{
	char	quote;
	char	*content;

	quote = exp->value[exp->i];
	start = exp->i;
	while (exp->value[exp->i] && exp->value[exp->i] != quote)
		exp->i++;
	content = ft_substr(exp->value, start, exp->i - start);
	append_str(exp, content);
	free(content);
}

void	handle_norexp_digits(t_expander *exp, size_t start)
{
	char	*content;

	while (ft_isdigit(exp->value[exp->i]))
		exp->i++;
	content = ft_substr(exp->value, start, exp->i - start);
	if (content && content[0] != '\0')
		append_str(exp, content + 1);
	free(content);
}

void	append_norexp_words(t_expander *exp, char *var_val)
{
	char	**words;
	int		i;

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

void	expand_norexp_var_else(t_expander *exp, size_t start)
{
	char	*var_name;
	char	*var_val;

	if (exp->value[exp->i] == '?')
		exp->i++;
	else
	{
		while (ft_isalnum(exp->value[exp->i]) || exp->value[exp->i] == '_')
			exp->i++;
	}
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
			append_norexp_words(exp, var_val);
		else
			append_str(exp, var_val);
	}
	free(var_name);
}

void	char_process(t_expander *exp)
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
