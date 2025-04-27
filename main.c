/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:47:34 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/27 14:47:13 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/global/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

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
	t_env	*status;

	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
		input = NULL;
	if (!input)
	{
		status = search_key("?", *env_list);
		if (status)
			exit(ft_atoi(status->val));
		clear_env(env_list, free);
		exit (0);
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

void	start_prompt(t_env *env_list, int fd)
{
	t_token			*tokens;
	t_shell			*cmd;
	char			*input;
	struct termios	settings;

	tcgetattr(fd, &settings);
	while (1)
	{
		catch_signals();
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
	int		fd;

	(void)av;
	fd = STDIN_FILENO;
	if (ac != 1)
		return (1);
	env_list = create_env(env);
	if (!env_list)
		exit (1);
	start_prompt(env_list, fd);
	return (0);
}
