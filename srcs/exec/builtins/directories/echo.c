/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:46:24 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 19:26:34 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	print_no_option(t_shell *cmnds, int size)
{
	int	i;
	int j;

	i = 1;
	if (size == 1)
		printf("\n");
	else if (size == 2)
		printf("%s\n", cmnds->args[1]);
	else if (size > 2)
	{
		while (cmnds->args[i])
		{
			j = 0;
			while (cmnds->args[i][j])
			{
				if (cmnds->args[i][j] == '"' || cmnds->args[i][j] == '\'')
					j++;
				printf("%c", cmnds->args[i][j]);
				j++;
			}
			if (i < size - 1)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}

void	print_with_option(t_shell *cmnds, int size)
{
		int	i;

	i = 2;
	if (size == 1)
		printf("");
	else if (size == 2)
		printf("%s", cmnds->args[1]);
	else if (size > 2)
	{
		while (cmnds->args[i])
		{
			printf("%s", cmnds->args[i]);
			if (i < size - 1)
				printf(" ");
			i++;
		}
	}
}

void	print_args(t_shell	*cmnds)
{
	int	size;

	size = arr_len(cmnds->args);
	if (improved_cmp(cmnds->args[1], "-n") == 0)
		print_with_option(cmnds, size);
	else
		print_no_option(cmnds, size);
}
