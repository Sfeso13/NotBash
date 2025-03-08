/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:47:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/08 01:48:57 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

//====================================================TESTS=====================================================//

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

//====================================================TESTS=====================================================//

volatile sig_atomic_t g_signal_received = 0;

pid_t	child_pid(int value, int setorget)
{
	static pid_t	pid;

	if (setorget == 1)
		pid = value;
	else
		return (pid);
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (!(waitpid(-1, NULL, WNOHANG))) // need to know about hanging child processes
		return ;//removed a new line printing
	g_signal_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	parser(char *input, t_env **env_list, t_shell **cmd, t_token **tokens)
{
	if (advsyncatcher(input, env_list) == 1)
	{
		free(input);
		return (1);
	}
	*tokens = tokenize(input);
	if (!(*tokens))
	{
		free(input);
		return (1);
	}
	analyze_in_expand(*tokens, *env_list);
	*cmd = fill_cmd(*tokens);
	return (0);
}

char	*get_input(t_env **env_list)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		clear_env(env_list, free);
		exit(0);
	}
	if (g_signal_received)
	{
		update_status(env_list, "1");
		g_signal_received = 0;
	}
	if (*input)
		add_history(input);
	return (input);
}

void	start_prompt(t_env *env_list)
{
	t_token	*tokens;
	t_shell	*cmd;
	char	*input;
	struct termios settings;
	int	fd;

	while (1)
	{
		fd = STDIN_FILENO;
		catch_signals();
		tcgetattr(fd, &settings);
		input = get_input(&env_list);
		if (displaymeagn(&input))
		{
			free(input);
			continue ;
		}
		if (parser(input, &env_list, &cmd, &tokens))
			continue ;
		// print_shell(cmd);
		execute(cmd, &env_list);
		tcsetattr(fd, TCSADRAIN, &settings);
		free(input);
		free_tokens(tokens);
		free_shell(cmd);
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_env	*env_list;

	(void)av;
	if (ac != 1)
		return (1);
	env_list = create_env(env);
	if (!env_list)
		exit (1);
	start_prompt(env_list);
	return (0);
}
