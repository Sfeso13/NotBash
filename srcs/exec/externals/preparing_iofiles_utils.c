/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:58:48 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/06 15:12:23 by yhossni          ###   ########.fr       */
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

int	*init_fds(void)
{
	static int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	return (fd);
}

int	fdop(int to_open, int append, char *filename, int write)
{
	if (close(to_open) == -1 && to_open != -1)
	{
		perror("close");
		exit(1);
	}
	if (!write)
		to_open = open(filename, O_RDONLY, 0777);
	else if (write && !append)
		to_open = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (write && append)
		to_open = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (to_open == -1)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (to_open);
}

int	what_in_to_open(t_token *tmp, int fd, t_redir *redir)
{
	if (tmp->type == TOKEN_REDIRECT_IN)
	{
		tmp = tmp->next;
		fd = fdop(fd, 0, tmp->value, 0);
		if (fd == -1)
			return (-1);
		redir->in_count[0]--;
	}
	else if (tmp->type == TOKEN_HEREDOC)
	{
		tmp = tmp->next;
		if (fd != -1)
			close(fd);
		fd = redir->docs[redir->doc_pos];
		redir->doc_pos++;
		if (fd == -1)
			return (-1);
		redir->in_count[1]--;
	}
	return (fd);
}

int	what_out_to_open(t_token *tmp, int fd, int *outredir)
{
	if (tmp->type == TOKEN_REDIRECT_OUT)
	{
		tmp = tmp->next;
		fd = fdop(fd, 0, tmp->value, 1);
		if (fd == -1)
			return (-1);
		(outredir[0])--;
	}
	else if (tmp->type == TOKEN_APPEND)
	{
		tmp = tmp->next;
		fd = fdop(fd, 1, tmp->value, 1);
		if (fd == -1)
			return (-1);
		(outredir[1])--;
	}
	return (fd);
}
