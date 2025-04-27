/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_nhelptwo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:00:32 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/27 17:00:56 by adechaji         ###   ########.fr       */
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
