/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_iofiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 15:51:26 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

char	*join_name(char *name, int i)
{
	char	*tmp;
	char	*num;

	tmp = name;
	num = ft_itoa(i);
	if (!num)
		return (NULL);
	name = ft_strjoin(tmp, num);
	if (!name)
	{
		free(num);
		return (NULL);
	}
	free(tmp);
	free(num);
	return (name);
}

char	*get_filename()
{
	int			fd;
	static int	i;
	char		*name;

	name = ft_strdup("/tmp/thd10101010doc");
	while (1)
	{
		name = join_name(name, i);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != -1)
		{
			i++;
			continue ;
		}
		fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd != -1)
		{
			close(fd);
			unlink(name);
			return (name);
		}
		free(name);
		i++;
	}
}

char	*read_input(int expandable, char *delim, int fd, t_env *env)
{
	char	*buff;

	buff = readline("> ");
	while (!buff)
		buff = readline("> ");
	while (buff && improved_cmp(buff, delim) != 0)
	{
		if (expandable)
			buff = expanddoc(buff, env);
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
		buff = readline("> ");
		while (!buff)
			buff = readline("> ");
	}
	return (buff);
}

int	get_doc(char *delim, t_env *env)
{
	char	*buff;
	int		fd;
	int		expandable;
	char	*tmp;
	char	*filename;

	expandable = 1;
	filename = get_filename();
	if (ft_strchr(delim, '\"') || ft_strchr(delim, '\''))
		expandable = 0;
	tmp = remove_doc_qts(delim);
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd == -1)
	{
		perror("heredoc fd");
		exit (1);
	}
	buff = read_input(expandable, tmp, fd, env);
	free(buff);
	close(fd);
	free(tmp);
	fd = open(filename, O_RDONLY, 0600);
	unlink(filename);
	free(filename);
	return (fd);
}

t_redir	init_redir_struct(t_token *args)
{
	t_redir redir;

	redir.in_count[0]= how_many_redir(args, TOKEN_REDIRECT_IN);
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

	fd  = init_fds(); //to free
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
			fd[0] = what_in_to_open(tmp, fd[0], redir.in_count, env);
		else if (tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_APPEND)
			fd[1] = what_out_to_open(tmp, fd[1], redir.out_count);
		if (redir.in_count[0] == 0 && redir.out_count[1] == 0 && redir.out_count[0] == 0 && redir.in_count[1] == 0)
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
