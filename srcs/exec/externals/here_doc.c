/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:58:33 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/22 15:33:54 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

char	*join_name(char *name, int *i)
{
	char	*tmp;
	char	*num;

	tmp = name;
	num = ft_itoa(*i);
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
	(*i)++;
	return (name);
}

char	*get_filename(void)
{
	int			fd;
	static int	i;
	char		*name;

	name = ft_strdup("/tmp/thd10101010doc");
	while (1)
	{
		name = join_name(name, &i);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != -1)
		{
			free(name);
			name = ft_strdup("/tmp/thd10101010doc");
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
	}
}

void	doc_sigint(int sig)
{
	rl_catch_signals = 0;
	(void)sig;
	g_signal_received = 1;
	write(1, "\n", 1);
	close(0);
}

char	*read_input(int expandable, char *delim, int fd, t_env *env)
{
	char	*buff;
	char	*tmp;

	signal(SIGINT, doc_sigint);
	buff = readline("> ");
	while (buff && improved_cmp(buff, delim) != 0)
	{
		if (expandable && ft_strchr(buff, '$'))
		{
			tmp = expanddoc(buff, env);
			free(buff);
			buff = tmp;
		}
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
		buff = readline("> ");
	}
	if (!buff && g_signal_received == 0)
		g_signal_received = 2;
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
		doc_err();
	buff = read_input(expandable, tmp, fd, env);
	if (!buff && g_signal_received == 1)
	{
		close(fd);
		unlink(filename);
		free(filename);
		free(tmp);
		return (-1);
	}
	return (prepare_doc(buff, tmp, fd, filename));
}
