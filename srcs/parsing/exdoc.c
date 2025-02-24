/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exdoc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:36:00 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/24 16:56:51 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	doc_append_str(char **str, size_t *len, size_t *cap, char *value)
{
	size_t	i;
	char	*new;
	size_t	new_cap;

	i = 0;
	if (!value)
		return (1);
	while (value[i])
	{
		if (*len + 1 >= *cap)
		{
			new_cap = *cap * 2;
			new = malloc(new_cap);
			if (!new)
				return (0);
			ft_memcpy(new, *str, *len);
			free(*str);
			*str = new;
			*cap = new_cap;
		}
		(*str)[(*len)++] = value[i++];
	}
	return (1);
}

static int	doc_append_char(char **str, size_t *len, size_t *cap, char c)
{
	char	*new;
	size_t	new_cap;

	if (*len + 1 >= *cap)
	{
		new_cap = *cap * 2;
		new = malloc(new_cap);
		if (!new)
			return (0);
		ft_memcpy(new, *str, *len);
		free(*str);
		*str = new;
		*cap = new_cap;
	}
	(*str)[(*len)++] = c;
	(*str)[*len] = '\0';
	return (1);
}

static int	handle_dollar(char *buff, int *i, t_exp *exp, t_env *env)
{
	char	*var;
	char	*val;
	int		start;

	(*i)++;
	if (buff[*i] == '?')
	{
		var = ft_strdup("?");
		val = get_env_value(var, env);
		if (val && !doc_append_str(&exp->res, &exp->len, &exp->cap, val))
			return (free(var), 0);
		free(var);
		(*i)++;
		return (1);
	}
	start = *i;
	if (!ft_isalpha(buff[*i]) && buff[*i] != '_')
	{
		if (!doc_append_char(&exp->res, &exp->len, &exp->cap, '$'))
			return (0);
		if (buff[*i] && !doc_append_char(&exp->res, &exp->len, &exp->cap, buff[*i]))
			return (0);
		*i += (buff[*i] != '\0');
		return (1);
	}
	while (ft_isalnum(buff[*i]) || buff[*i] == '_')
		(*i)++;
	var = ft_substr(buff, start, *i - start);
	val = get_env_value(var, env);
	if (val && !doc_append_str(&exp->res, &exp->len, &exp->cap, val))
		return (free(var), 0);
	free(var);
	return (1);
}

char	*expanddoc(char *buff, t_env *env)
{
	t_exp	exp;
	int		i;

	exp = (t_exp){.cap = 16, .res = ft_calloc(16, 1)};
	i = 0;
	while (exp.res && buff[i])
	{
		if (buff[i] == '$' && handle_dollar(buff, &i, &exp, env))
			continue ;
		if (!doc_append_char(&exp.res, &exp.len, &exp.cap, buff[i]))
			break ;
		i++;
	}
	if (!exp.res || !doc_append_char(&exp.res, &exp.len, &exp.cap, '\0'))
		return (free(exp.res), NULL);
	return (exp.res);
}
