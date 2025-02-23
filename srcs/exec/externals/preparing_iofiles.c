/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 20:47:59 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	get_doc(char *delim, t_env *env)
{
	char	*buff;
	int		fd;
	(void)env;

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

int	*get_io_files(t_token *args, t_env *env)
{
	int		*fd;
	int		in_count[2];
	int		out_count[2];
	// int		append;
	// int		doc;
	t_token	*tmp;

	fd  = init_fds(); //to free
	in_count[0]= how_many_redir(args, TOKEN_REDIRECT_IN);
	out_count[0] = how_many_redir(args, TOKEN_REDIRECT_OUT);
	out_count[1] = how_many_redir(args, TOKEN_APPEND);
	in_count[1] = how_many_redir(args, TOKEN_HEREDOC);
	tmp = args;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_HEREDOC)
			fd[0] = what_in_to_open(tmp, fd[0], in_count, env);
		else if (tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_APPEND)
			fd[1] = what_out_to_open(tmp, fd[1], out_count);
		if (in_count[0] == 0 && out_count[1] == 0 && out_count[0] == 0 && in_count[1] == 0)
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
	if (fd[0] != -1)
	{
		ft_dup(fd[0], 0);
	}
	if (fd[1] != -1)
	{
		ft_dup(fd[1], 1);
	}
}
