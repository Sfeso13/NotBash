/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:28:52 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/06 14:50:17 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	prepare_doc(char *buff, char *tmp, int fd, char *filename)
{
	free(buff);
	close(fd);
	free(tmp);
	fd = open(filename, O_RDONLY, 0600);
	unlink(filename);
	free(filename);
	return (fd);
}

void	doc_err(void)
{
	perror("heredoc fd");
	exit (1);
}

void	process_docs(t_token *args, t_redir *redir, t_env *env)
{
	int	i;

	i = 0;
	while (i < redir->in_count[1])
	{
		if (args->type == TOKEN_HEREDOC)
		{
			redir->docs[i] = get_doc(args->next->value, env);
			i++;
		}
		args = args->next;
	}
}

void	clear_docs(t_redir *redir)
{
	int	i;

	i = 0;
	while (i < redir->in_count[1])
	{
		close(redir->docs[i]);
		i++;
	}
}
