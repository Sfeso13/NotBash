/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:17:42 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/09 15:05:44 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

void	fd_err(t_fd fds, t_shell **cmnds, int *i)
{
	g_signal_received = 0;
	close(fds.pfd[1]);
	fds.infd = fds.pfd[0];
	*cmnds = (*cmnds)->next;
	(*i)++;
}

void	execute_p(t_fd *fds, int *fd, t_shell **cmnds, t_env **env)
{
	piped_exec(*cmnds, fd, *fds, env);
	fds->infd = fds->pfd[0];
	*cmnds = (*cmnds)->next;
}

t_redir	multi_init_redir(t_shell *cmnds)
{
	t_redir	redir;
	t_token	*args;
	int		i;

	i = 0;
	redir.in_count[0] = 0;
	redir.in_count[1] = 0;
	redir.out_count[0] = 0;
	redir.out_count[1] = 0;
	while (cmnds)
	{
		args = cmnds->tokens;
		redir.in_count[0] += how_many_redir(args, TOKEN_REDIRECT_IN);
		redir.in_count[1] += how_many_redir(args, TOKEN_HEREDOC);
		redir.out_count[0] += how_many_redir(args, TOKEN_REDIRECT_OUT);
		redir.out_count[1] += how_many_redir(args, TOKEN_APPEND);
		i++;
		cmnds = cmnds->next;
	}
	redir.doc_pos = 0;
	return (redir);
}

int	search_multi(t_shell *cmnds, t_token_type type)
{
	int	i;

	i = 0;
	while (cmnds)
	{
		if (search_token(cmnds->tokens, type))
			i++;
		cmnds = cmnds->next;
	}
	return (i);
}

void	multi_doc_process(t_redir *redir, t_shell *cmnds, t_env *env)
{
	int		i;
	t_token	*args;

	i = 0;
	while (cmnds && i < redir->in_count[1])
	{
		args = cmnds->tokens;
		while (args)
		{
			if (args->type == TOKEN_HEREDOC)
			{
				redir->docs[i] = get_doc(args->next->value, env);
				if (redir->docs[i] == -1)
					return ;
				i++;
			}
			args = args->next;
		}
		cmnds = cmnds->next;
	}
	signal(SIGINT, handle_sigint);
}
