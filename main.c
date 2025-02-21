/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:47:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 20:01:30 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

//====================================================TESTS=====================================================//
#include <stdio.h>

#include <stdio.h>

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

	i = 1;
	while (shell)
	{
		printf("\n===== Command %d =====\n\n", i);
		token = shell->tokens;
		while (token)
		{
			printf("  Token: %-10s | Type: %s\n\n",
				token->value, get_token_name(token->type));
			token = token->next;
		}
		printf("\n==================end=======================\n\n");
		if (shell->next)
			printf("  -> Next Command Exists\n");
		shell = shell->next;
		i++;
	}
}

//====================================================TESTS=====================================================//


int main(int ac, char *av[], char *env[])
{
	t_token	*tokens;
	t_shell	*cmd;
	char	*input;
	// t_env	*env_list;

	(void)env;
	(void)av;
	if (ac != 1)
		return (1);
    // env_list = create_env(env);
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
		cmd	= fill_cmd(tokens);
		if (!cmd)
		{
			free_tokens(tokens);
			free(input);
			exit(1);
		}
		//quotes_remove(tokens);
		print_shell(cmd);
		// execute(cmd, env_list);
		free(input);
		free_tokens(tokens);
	}
	return 0;
}
