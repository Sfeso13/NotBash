/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:46:24 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/26 13:11:39 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

void	print_no_option(t_token *cmnd, int size)
{
	int	i;

	i = 1;
	if (size == 1)
		printf("\n");
	else if (size == 2)
		printf("%s\n", cmnd->next->value);
	else if (size > 2)
	{
		cmnd = cmnd->next;
		while (cmnd && cmnd->type == TOKEN_WORD)
		{
			printf("%s", cmnd->value);
			if (i < size)
				printf(" ");
			i++;
			cmnd = cmnd->next;
		}
		printf("\n");
	}
}

void	print_with_option(t_token *cmnd, int size)
{
	int	i;

	i = 2;
	if (size == 2)
		printf("");
	else if (size == 3)
		printf("%s", cmnd->next->value);
	else if (size > 3)
	{
		cmnd = cmnd->next;
		while (cmnd && cmnd->type == TOKEN_WORD)
		{
			printf("%s", cmnd->value);
			if (i < size - 1)
				printf(" ");
			i++;
			cmnd = cmnd->next;
		}
	}
}

void	print_args(t_token	*cmnd, t_env *env)
{
	int	size;

	size = how_many_args(cmnd, TOKEN_WORD);
	if (size > 1 && improved_cmp(cmnd->next->value, "-n") == 0)
		print_with_option(cmnd->next, size);
	else
		print_no_option(cmnd, size);
	update_status(&env, "0");
}
