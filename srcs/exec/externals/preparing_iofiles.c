/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 12:22:56 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	how_many_redir(t_token *cmnd, t_token_type type)
{
	int	count;

	count = 0;
	while (cmnd)
	{
		if (cmnd->type == type)
			count++;
		cmnd = cmnd->next;
	}
	return (count);
}

int	*init_fds()
{
	int	*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (!fd)
		return (NULL);
	fd[0] = -1;//to change
	fd[1] = -1;
	return (fd);
}

int	*get_io_files(t_token *args)
{
	int		*fd;
	int		inredir;
	int		outredir;
	int		append;
	t_token	*tmp;

	fd  = init_fds(); //to free
	inredir = how_many_redir(args, TOKEN_REDIRECT_IN);
	outredir = how_many_redir(args, TOKEN_REDIRECT_OUT);
	append = how_many_redir(args, TOKEN_APPEND);
	tmp = args;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN)
		{
			tmp = tmp->next;
			close(fd[0]);
			fd[0] = open(tmp->value, O_RDONLY, 0777);
			if (fd[0] == -1)
				perror("fd: ");//should kill child here
			inredir--;
		}
		else if (tmp->type == TOKEN_REDIRECT_OUT)
		{
			tmp = tmp->next;
			close(fd[1]);
			if (append > 0)
				fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
			else
				fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd[1] == -1)
				perror("fd :");
			outredir--;
		}
		if (inredir == 0 && outredir == 0)
			break ;
		tmp = tmp->next;
	}
	return (fd);
}
