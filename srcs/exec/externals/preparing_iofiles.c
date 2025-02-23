/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 18:12:48 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	get_doc(char *delim)
{
	char	*buff;
	int		fd;

	fd = open("/tmp/thd10101010doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("heredoc fd");
		exit (1);
	}
	buff = readline("> ");
	while (buff && improved_cmp(buff, delim) != 0)
	{
		//expantion
		//delim has quotes -> call expand
		//not have quote -> doz
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
		buff = readline("> ");
	}
	free(buff);
	close(fd);
	fd = open("/tmp/thd10101010doc", O_RDONLY);
	unlink("/tmp/thd10101010doc");
	return (fd);
}

int	*get_io_files(t_token *args)
{
	int		*fd;
	int		inredir;
	int		outredir;
	int		append;
	int		doc;
	t_token	*tmp;

	fd  = init_fds(); //to free
	inredir = how_many_redir(args, TOKEN_REDIRECT_IN);
	outredir = how_many_redir(args, TOKEN_REDIRECT_OUT);
	append = how_many_redir(args, TOKEN_APPEND);
	doc = how_many_redir(args, TOKEN_HEREDOC);
	tmp = args;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_HEREDOC)
			fd[0] = what_in_to_open(tmp, fd[0], &inredir, &doc);
		else if (tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_APPEND)
			fd[1] = what_out_to_open(tmp, fd[1], &outredir, &append);
		if (inredir == 0 && outredir == 0 && append == 0 && doc == 0)
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

void	redirect(t_token *cmnd)
{
	int		*fd;

	fd = get_io_files(cmnd);
	if (fd[0] != -1)
	{
		ft_dup(fd[0], 0);
	}
	if (fd[1] != -1)
	{
		ft_dup(fd[1], 1);
	}
}
