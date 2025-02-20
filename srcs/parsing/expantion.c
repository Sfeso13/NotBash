/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:29:02 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/20 01:25:03 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

void	expantions(t_token *cmd)
{
	char	*expaded;

	while (cmd)
	{
		expaded = expand_it(cmd->value);
		free(cmd->value);
		cmd->value = expaded;
		cmd = cmd->next;
	}
}

static void	handle_quotes(char c, t_expand *ex)
{
	if (c == '\'' && !ex->in_double)
		ex->in_single = !ex->in_single;
	else if (c == '\"' && !ex->in_single)
		ex->in_double = !ex->in_double;
}

static size_t	get_var_length(const char **str)
{
	const char	*start;
	char		var_name[256];
	size_t		len;
	char		*value;

	start = *str + 1;
	len = 0;
	while (ft_isalnum(**str) || **str == '_')
	{
		(*str)++;
		len++;
	}
	if (len == 0)
		return (1);
	ft_strncpy(var_name, start, len);
	var_name[len] = '\0';
	value = getenv(var_name);
	if (value)
		return (ft_strlen(value));
	return (0);
}

// static void	skip_quotes(const char **p, t_expand *ex)
// {
// 	if ((**p == '\'' && !ex->in_double) || (**p == '\"' && !ex->in_single))
// 		(*p)++;
// }

size_t	calculate_buf_size(const char *token)
{
	t_expand	ex;
	const char	*p;

	ex = (t_expand){0};
	p = token;
	while (*p)
	{
		handle_quotes(*p, &ex);
		//skip_quotes(&p, &ex);
		if (*p == '$' && !ex.in_single)
		{
			p++;
			ex.idx += get_var_length(&p);
		}
		else if (*p)
			ex.idx += !!(*p++);
	}
	return (ex.idx + 1);
}

static void	insert_var(const char **str, char *buf, size_t *idx)
{
	const char  *start;
	char		var_name[256];
	size_t		len;
	char		*value;

	start = ++(*str);
	len = 0;
	while (ft_isalnum(**str) || **str == '_')
	{
		(*str)++;
		len++;
	}
	if (len == 0)
		buf[(*idx)++] = '$';
	else
	{
		ft_strncpy(var_name, start, len);
		var_name[len] = '\0';
		value = getenv(var_name);
		if (value)
		{
			ft_strcpy(buf + *idx, value);
			*idx += ft_strlen(value);
		}
	}
}

void	fill_buffer(const char *token, char *buf)
{
	t_expand	ex;
	const char	*p;

	ex = (t_expand){0};
	p = token;
	while (*p)
	{
		handle_quotes(*p, &ex);
		//skip_quotes(&p, &ex);
		if (*p == '$' && !ex.in_single)
			insert_var(&p, buf, &ex.idx);
		else if (*p)
			buf[ex.idx++] = *p++;
	}
	buf[ex.idx] = '\0';
}
char	*expand_it(char *token)
{
	char	*buf;
	size_t	size;

	if (!token)
		return (NULL);
	size = calculate_buf_size(token);
	buf = malloc(size);
	if (!buf)
		return (NULL);
	fill_buffer(token, buf);
	return (buf);
}
