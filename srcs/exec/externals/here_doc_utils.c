/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:28:52 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/05 00:29:09 by yhossni          ###   ########.fr       */
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
