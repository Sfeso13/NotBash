/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:09:57 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 17:11:00 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

char	*nl_search(const char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	if (s[i] == '\n')
		return ((char *)(s + i));
	return (NULL);
}

char	*buff_read(int fd, char *buffer, char *tmp, char *tmp2)
{
	ssize_t	bytes_read;

	while (!nl_search(buffer))
	{
		tmp = (char *)malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (free(buffer), NULL);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(tmp);
			break ;
		}
		tmp[bytes_read] = '\0';
		tmp2 = buffer;
		buffer = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	if (bytes_read < 0)
	{
		free(buffer);
		return (tmp = NULL, buffer = NULL, NULL);
	}
	return (tmp = NULL, tmp2 = NULL, buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	char		*line;
	size_t		line_len;

	if (fd < 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = buff_read(fd, buffer, tmp = NULL, line = NULL);
	if (!buffer || *buffer == '\0')
		return (free(buffer), buffer = NULL, NULL);
	if (nl_search(buffer))
	{
		line_len = nl_search(buffer) - buffer + 1;
		line = (char *)malloc(line_len + 1);
		if (!line)
			return (free(buffer), buffer = NULL, NULL);
		ft_strlcpy(line, buffer, line_len + 1);
		tmp = ft_substr(buffer, line_len, ft_strlen(buffer));
		free(buffer);
		return (buffer = tmp, tmp = NULL, line);
	}
	tmp = buffer;
	buffer = NULL;
	return (tmp);
}
