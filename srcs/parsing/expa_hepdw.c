/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_hepdw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:44:01 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/09 00:11:04 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int	checkvalidation(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"')
			|| (str[i] == '\'' && str[i + 1] == '\''))
			return (0);
		i++;
	}
	return (1);
}

int	bfrafters(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (0);
}
void	chinexpdola(t_token *current, int *inexp, int *dol)
{
	if (improved_cmp(current->value, "export") == 0
		&& ((current->next) && bfrafters(current->next->value) == 0))
		*inexp = 1;
	if (ft_strchr(current->value, '$'))
		*dol = 1;
	else
		*dol = 0;
}

void	expprocetoken(t_token *current, t_env *env, int inexp, int dol)
{
	t_expander	exp;
	char		*or_val;
	int			wrds;

	or_val = current->value;
	exp = expand_token(or_val, env, inexp);
	current->value = exp.buffer;
	free(or_val);
	if (dol == 1)
		wrds = count_custom_words(current->value);
	if (ft_strchr(current->value, '\x01') && inexp == 0)
		split_and_insert(current);
	if ((current->prev) && (current->prev->type == TOKEN_REDIRECT_OUT
			|| current->prev->type == TOKEN_REDIRECT_IN
			|| current->prev->type == TOKEN_APPEND) && dol != 0)
	{
		if (wrds != 1)
			current->ambiguous = 1;
	}
	current->expanded = 1;
	if (exp.ignoreme == 1)
		current->ignore = 1;
}
