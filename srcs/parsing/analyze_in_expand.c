/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_in_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:21:30 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/28 14:29:01 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

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

int	count_p_cmnds(t_token *token)
{
	int	wrdcount;

	wrdcount = 0;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			break ;
		wrdcount++;
		token = token->next;
	}
	return (wrdcount);
}

void	test(t_token **token, t_env *env)
{
	int	wrdcount;

	wrdcount = count_p_cmnds(*token);
	while (wrdcount > 0)
	{
		proc_token_exp(*token, env);
		*token = (*token)->next;
		wrdcount--;
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
		test(&current, env);
		while (current && current->type != TOKEN_PIPE)
			current = current->next;
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (0);
}
