/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:14:06 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/24 20:42:34 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

t_token	*search_token(t_token *token, t_token_type type)
{
	while (token)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	piped_exec(t_token *cmnd, int in, int out, t_env *env)
{
	pid_t	child;
	char	*path;
	char	**args;

	child = fork();
	if (child < 0)
		printf("fork error!\n");//to handle appropriately
	else if (child == 0)
	{
		args = prepare_args(cmnd);
		path = get_cmnd_path(cmnd, env);
		// printf("cmnd path : %s\n", path);
		if (in != -1)
			ft_dup(in, 0);
		if (out != -1)
			ft_dup(out, 1);
		if (path)
			run_command(path, args, env);
		else
			printf("%s: command not found\n", cmnd->value);
		exit(0);
	}
}

void	multiple_process_exec(t_shell *cmnds, int process_count, t_env *env)
{
	int	i;
	int	pfd[2];
	int	*fd;
	int	infd;
	int	outfd;
	char	*stat;
	int		status;
	pid_t	childpid;

	i = 0;
	infd = -1;
	outfd = -1;
	while (i < process_count)
	{
		fd = get_io_files(cmnds->tokens, env);
		if (pipe(pfd) == -1)
		{
			perror("pipe");
			exit(-1);
		}
		if (fd[1] == -1 && i < process_count - 1)
		{
			if (outfd != -1)
				close(outfd);
			outfd = pfd[1];
		}
		else if (i < process_count - 1)
		{
			if (outfd != -1)
				close(outfd);
			outfd = fd[1];
			close(pfd[1]);
		}
		else
		{
			if (outfd != -1)
				close(outfd);
			outfd = -1;
			close(pfd[1]);
		}
		if (fd[0] != -1)
		{
			if (infd != -1)
				close(infd);
			infd = fd[0];
		}
		piped_exec(extract_cmd(cmnds->tokens), infd, outfd, env);
		if (infd != -1)
			close(infd);
		infd = pfd[0];
		i++;
		cmnds = cmnds->next;
	}
	while (1)
	{
		childpid = wait(&status);
		if (childpid == -1)
		{
			if (errno == ECHILD)
				break ;
			else
			{
				perror("wait");
				exit(-1);
			}
		}
		stat = ft_itoa(status);
		printf("child exited with status : %d\n", status);
		update_status(&env, stat);
		free(stat);
	}
}

void	single_process_exec(t_shell *cmnds, t_env *env)
{
	t_token	*cmnd;
	t_env	*dash;

	cmnd = extract_cmd(cmnds->tokens);
	if (!cmnd)
	{
		dash = search_key("_", env);
		return (set_env_value(&dash, NULL));
	}
	update_dash(cmnd, &env);
	if (isbuiltin(cmnd->value))
		which_builtin(cmnds, cmnd, env);
	else
		external_cmd(cmnds, cmnd, env);
}

void	execute(t_shell *cmnds, t_env *env)
{
	int		process_count;

	process_count = how_many_processes(cmnds);
	if (process_count == 1)
		single_process_exec(cmnds, env);
	else
		multiple_process_exec(cmnds, process_count, env);
}
