/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:47:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 01:20:00 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

//====================================================TESTS=====================================================//
const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case TOKEN_WORD:
            return "WORD";
        case TOKEN_PIPE:
            return "PIPE";
        case TOKEN_REDIRECT_IN:
            return "REDIRECT_IN";
        case TOKEN_REDIRECT_OUT:
            return "REDIRECT_OUT";
        case TOKEN_APPEND:
            return "APPEND";
        case TOKEN_HEREDOC:
            return "HEREDOC";
        case TOKEN_EOF:
            return "EOF";
        default:
            return "UNKNOWN";
    }
}

void print_token_details(t_token *tokens)
{
    if (!tokens)
    {
        printf("No tokens to display.\n");
        return;
    }

    printf("=== Parsed Tokens ===\n");

    int pos = 1; // Start token numbering from 1
    for (t_token *t = tokens; t; t = t->next)
    {
        // Print the token number, value, and type
        printf("\nToken #%d:\n", pos);
        printf("  Token: %-15s Type: %-15s\n", t->value, token_type_to_string(t->type)); // Using token_type_to_string for type
        pos++; // Increment position for each token
    }

    printf("\n======================\n");
}
//====================================================TESTS=====================================================//


int main(int ac, char *av[], char *env[])
{
    t_token *tokens;
	char	*input;
	t_env	*env_list;

	(void)av;
	if (ac != 1)
		return (1);
    env_list = create_env(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (displaymeagn(&input))
		{
			free(input);
			continue ;
		}
		if (advsyncatcher(input) == 1)
		{
			free(input);
			continue ;
		}
		tokens = tokenize(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		expantions(tokens);
		print_token_details(tokens);
		// execute(cmd, env_list);
		free(input);
		free_tokens(tokens);
	}
	return 0;
}
