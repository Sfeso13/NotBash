/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_nhelptwo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:00:32 by adechaji          #+#    #+#             */
/*   Updated: 2025/05/05 19:04:44 by adechaji         ###   ########.fr       */
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
	if (!content)
		exp->emptynot = 1;
	else
		exp->emptynot = 0;
	append_str(exp, content);
	free(content);
}

char	*trim_end(char *s1, char const *set)
{
	char	*newstr;
	int		first;
	int		len;
	int		last;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1) - 1;
	while (last >= first && checkerr(set, s1[last]))
		last--;
	len = last - first + 1;
	if (len == 0)
		return (NULL);
	newstr = ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_memcpy(newstr, s1 + first, len);
	return (newstr);
}

void	exp_check_sides(t_expander *exp)
{
	char	*dol;

	dol = ft_strchr(exp->value, '$');
	if (dol != exp->value)
	{
		if (!iswhitespace(*(dol - 1)))
			exp->surr_before = 1;
	}
	if ((exp->value ) && exp->value[exp->i] && \
					!iswhitespace(exp->value[exp->i]))
		exp->surr_after = 1;
}

int	doublequoted(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = ft_strlen(str);
	if (str[0] == '\"' && str[i - 1] == '\"')
		return (1);
	return (0);
}
