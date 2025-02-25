/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exdochelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:54:30 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/25 13:07:20 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	handle_qst_mark(int *i, t_exp *exp, t_env *env)
{
	char	*var;
	char	*val;

	var = ft_strdup("?");
	if (!var)
		return (0);
	val = get_env_value(var, env);
	if (val && !doc_append_str(&exp->res, &exp->len, &exp->cap, val))
		return (free(var), 0);
	free(var);
	(*i)++;
	return (1);
}

int	doc_handle_invalids(char *buff, int *i, t_exp *exp)
{
	if (!doc_append_char(&exp->res, &exp->len, &exp->cap, '$'))
		return (0);
	if (buff[*i] && !doc_append_char(&exp->res, &exp->len,
			&exp->cap, buff[*i]))
		return (0);
	*i += (buff[*i] != '\0');
	return (1);
}

int	doc_handle_valids(char *buff, int *i, t_exp *exp, t_env *env)
{
	char	*var;
	char	*val;
	int		start;

	start = *i;
	while (ft_isalnum(buff[*i]) || buff[*i] == '_')
		(*i)++;
	var = ft_substr(buff, start, *i - start);
	if (!var)
		return (0);
	val = get_env_value(var, env);
	if (val && !doc_append_str(&exp->res, &exp->len, &exp->cap, val))
		return (free(var), 0);
	free(var);
	return (1);
}
