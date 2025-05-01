/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:54:37 by yhossni           #+#    #+#             */
/*   Updated: 2025/05/01 09:56:41 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

int	checkdir(char *s)
{
	struct stat	path;

	stat(s, &path);
	if (S_ISDIR(path.st_mode))
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (-2);
	}
	return (0);
}

int	is_absolute(t_token *cmnd)
{
	int	check;

	if (ft_strchr(cmnd->value, '/'))
	{
		check = checkdir(cmnd->value);
		if (check == -2)
			return (-2);
		if (access(cmnd->value, F_OK) == 0)
		{
			if (access(cmnd->value, X_OK) == 0)
				return (1);
			ft_putstr_fd(cmnd->value, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (2);
		}
		ft_putstr_fd(cmnd->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}
