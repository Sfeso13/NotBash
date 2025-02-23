/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:58:48 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 20:25:22 by adechaji         ###   ########.fr       */
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
		perror("input open");//should kill child here
		exit(1);
	}
	return (to_open);
}

int	what_in_to_open(t_token *tmp, int fd, int *inredir, int *doc)
{
	if (tmp->type == TOKEN_REDIRECT_IN)
	{
		tmp = tmp->next;
		fd = fdop(fd, 0, tmp->value, 0);
		inredir--;
	}
	else if (tmp->type == TOKEN_HEREDOC)
	{
		tmp = tmp->next;
		fd = get_doc(tmp->value);
		doc--;
	}
	return (fd);
}

int	what_out_to_open(t_token *tmp, int fd, int *outredir, int *append)
{
	if (tmp->type == TOKEN_REDIRECT_OUT)
	{
		tmp = tmp->next;
		fd = fdop(fd, 0, tmp->value, 1);
		(*outredir)--;
	}
	else if (tmp->type == TOKEN_APPEND)
	{
		tmp = tmp->next;
		fd = fdop(fd, 1, tmp->value, 1);
		(*append)--;
	}
	return (fd);
}
