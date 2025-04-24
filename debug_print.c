/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:21:27 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/24 18:44:05 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

const char	*get_token_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == TOKEN_APPEND)
		return ("APPEND");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_EOF)
		return ("EOF");
	return ("UNKNOWN");
}

void	print_shell(t_shell *shell)
{
	int		i;
	t_token	*token;
	char	prev_info[64];

	i = 1;
	if (!shell)
		printf("No commands in pipeline\n");
	while (shell)
	{
		printf("\n=== Command %d ===\n", i++);
		token = shell->tokens;
		while (token)
		{
			if (token->prev)
				snprintf(prev_info, sizeof(prev_info),
					"%-10s (%s)", token->prev->value,
					get_token_name(token->prev->type));
			else
				snprintf(prev_info, sizeof(prev_info), "%-10s", "(None)");
			printf("  %-15s %-12s Expanded: %-3d ← Prev: %s\n",
				token->value,
				get_token_name(token->type),
				token->expanded,
				prev_info);
			if (token->ambiguous == 0)
				printf("not ambi\n");
			else if (token->ambiguous == 1)
				printf("is ambi\n");
			else
				printf("smtg is wrong %d\n", token->ambiguous);
			token = token->next;
		}
		printf("=====================\n");
		printf("Prev cmd: %-14p Next cmd: %p\n",
			(void *)shell->prev, (void *)shell->next);
		shell = shell->next;
	}
}
