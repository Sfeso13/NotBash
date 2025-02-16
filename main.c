/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:47:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 09:57:51 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/includes/minishell.h"

//====================================================TESTS=====================================================//
void print_cmd(t_shell *cmd)
{
    if (!cmd)
        return;

    printf("  Args: ");
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i]; i++)
            printf("[%s] ", cmd->args[i]);
    }
    else
    {
        printf("NULL");
    }
    printf("\n");
    printf("  Input File: %s\n", cmd->infile ? cmd->infile : "NULL");
    printf("  Output File: %s\n", cmd->outfile ? cmd->outfile : "NULL");
    printf("  Append Mode: %s\n", cmd->append_mode ? "yes" : "no");
    printf("  Heredoc Delimiter: %s\n", cmd->heredoc_dlm ? cmd->heredoc_dlm : "NULL");
    printf("  Has Next Command: %s\n", cmd->next ? "yes" : "no");
    printf("  Has Previous Command: %s\n", cmd->prev ? "yes" : "no");
}

void print_pipeline(t_shell *head)
{
    t_shell *current = head;
    int cmd_num = 1;

    printf("\n=== Parsed Commands ===\n");
    while (current)
    {
        printf("\nCommand #%d:\n", cmd_num++);
        print_cmd(current);
        if (current->next)
            printf("  ---> Piped to next command --->\n");
        current = current->next;
    }
    printf("\n========================\n");
}
//====================================================TESTS=====================================================//


int main()
{
	t_shell	*cmd;
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (quoting_check(input))
		{
			printf("minishell: syntax error: unclosed quotes\n");
			free(input);
			continue ;
		}
		cmd = inparse(input);
		if (!cmd)
		{
			free(input);
			continue;
		}
		free(input);
		print_pipeline(cmd);
		free_cmd(cmd);
	}
	return 0;
}
