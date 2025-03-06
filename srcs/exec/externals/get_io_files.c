/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:52 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/06 00:07:53 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	check_doc_limit(int count)
{
	if (count > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		return (0);
	}
	return (1);
}

int	handleinput(t_token *tmp, int *fd, t_redir redir, t_env *env)
{
	fd[0] = what_in_to_open(tmp, fd[0], redir.in_count, env);
	if (fd[0] == -1)
	{
		if (fd[1])
			close(fd[1]);
		return (0);
	}
	return (1);
}

int	handleoutput(t_token *tmp, int *fd, t_redir redir)
{
	fd[1] = what_out_to_open(tmp, fd[1], redir.out_count);
	if (fd[1] == -1)
	{
		if (fd[0])
			close(fd[0]);
		return (0);
	}
	return (1);
}

int	*opening(t_token *args, int *fd, t_redir redir, t_env *env)
{
	while (args)
	{
		if (args->next && is_ambi(args->next))
			return (NULL);
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

int	*get_io_files(t_token *args, t_env *env)
{
	int		*fd;
	t_redir	redir;

	fd = init_fds();
	redir = init_redir_struct(args);
	if (!check_doc_limit(redir.in_count[1]))
		return (update_status(&env, "1"), NULL);
	fd = opening(args, fd, redir, env);
	return (fd);
}
