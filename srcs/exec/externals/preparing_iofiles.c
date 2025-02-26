/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 13:21:59 by yhossni          ###   ########.fr       */
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

int	*get_io_files(t_token *args, t_env *env)
{
	int		*fd;
	t_redir	redir;
	t_token	*tmp;

	fd = init_fds();
	redir = init_redir_struct(args);
	if (redir.in_count[1] > 16)
	{
		printf("maximum here-document count exceeded\n");// handle error better
		exit(2);
	}
	tmp = args;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_HEREDOC)
		{
			fd[0] = what_in_to_open(tmp, fd[0], redir.in_count, env);
			if (fd[0] == -1)
				return (NULL);
		}
		else if (tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_APPEND)
		{
			fd[1] = what_out_to_open(tmp, fd[1], redir.out_count);
			if (fd[1] == -1)
				return (NULL);
		}
		if (redir.in_count[0] == 0 && redir.out_count[1] == 0 && \
			redir.out_count[0] == 0 && redir.in_count[1] == 0)
			break ;
		tmp = tmp->next;
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
