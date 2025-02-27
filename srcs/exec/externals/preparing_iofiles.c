/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/27 12:24:38 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

t_redir	init_redir_struct(t_token *args)
{
	t_redir	redir;

	redir.in_count[0] = how_many_redir(args, TOKEN_REDIRECT_IN);
	redir.in_count[1] = how_many_redir(args, TOKEN_HEREDOC);
	redir.out_count[0] = how_many_redir(args, TOKEN_REDIRECT_OUT);
	redir.out_count[1] = how_many_redir(args, TOKEN_APPEND);
	return (redir);
}

int	check_doc_limit(int count)
{
	if (count > 16)
	{
		printf("maximum here-document count exceeded\n");
		return (0);
	}
	return (1);
}

int	handleinput(t_token *tmp, int *fd, t_redir redir, t_env *env)
{
	fd[0] = what_in_to_open(tmp, fd[0], redir.in_count, env);
	if (fd[0] == -1)
		return (0);
	return (1);
}

int	handleoutput(t_token *tmp, int *fd, t_redir redir)
{
	fd[1] = what_out_to_open(tmp, fd[1], redir.out_count);
	if (fd[1] == -1)
		return (0);
	return (1);
}

int	*get_io_files(t_token *args, t_env *env)
{
	int		*fd;
	t_redir	redir;

	fd = init_fds();
	redir = init_redir_struct(args);
	if (!check_doc_limit(redir.in_count[1]))
		return (NULL);
	while (args)
	{
		if (args->type == TOKEN_REDIRECT_IN || args->type == TOKEN_HEREDOC)
		{
			if (!handleinput(args, fd, redir, env))
				return (NULL);
		}
		else if (args->type == TOKEN_REDIRECT_OUT || args->type == TOKEN_APPEND)
		{
			if (!handleoutput(args, fd, redir))
				return (NULL);
		}
		if (redir.in_count[0] == 0 && redir.out_count[1] == 0 && \
			redir.out_count[0] == 0 && redir.in_count[1] == 0)
			break ;
		args = args->next;
	}
	return (fd);
}

void	ft_dup(int from, int to)
{
	if (dup2(from, to) == -1)
	{
		perror("dup");
		exit(1);
	}
	if (close(from) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	redirect(t_token *cmnd, t_env *env)
{
	int		*fd;

	fd = get_io_files(cmnd, env);
	if (!fd)
		exit(1);
	if (fd[0] != -1)
	{
		ft_dup(fd[0], 0);
	}
	if (fd[1] != -1)
	{
		ft_dup(fd[1], 1);
	}
}
