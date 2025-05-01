/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/05/01 09:58:32 by yhossni          ###   ########.fr       */
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
	redir.doc_pos = 0;
	return (redir);
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

int	is_ambi(t_token *args)
{
	if (args->ambiguous == 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (1);
	}
	return (0);
}

int	check_ambi(t_token *cmnd)
{
	while (cmnd)
	{
		if (cmnd->ambiguous == 1)
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (1);
		}
		cmnd = cmnd->next;
	}
	return (0);
}

int	*init_fds(void)
{
	static int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	return (fd);
}
