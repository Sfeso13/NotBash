/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:46:24 by yhossni           #+#    #+#             */
/*   Updated: 2025/04/24 18:40:02 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/exec/exec.h"

int	is_option(char *s)
{
	size_t	i;
	size_t	len;

	i = 1;
	if (improved_cmp(s, "-n") == 0)
		return (1);
	len = ft_strlen(s);
	if (s[0] == '-' && len > 1)
	{
		while (s[i] && s[i] == 'n')
			i++;
		if (i == len)
			return (1);
	}
	return (0);
}

void	print_no_option(t_token *cmnd, int size)
{
	int	i;

	i = 1;
	if (size == 1)
		printf("\n");
	else if (size == 2 && cmnd)
		printf("%s\n", cmnd->value);
	else if (size > 2)
	{
		while (cmnd)
		{
			if (cmnd->type == TOKEN_WORD && (!cmnd->prev || \
				!redir_token(cmnd->prev)))
			{
				printf("%s", cmnd->value);
				i++;
				if (i < size)
					printf(" ");
			}
			cmnd = cmnd->next;
		}
		printf("\n");
	}
}

void	print_with_option(t_token *cmnd, int size, int i)
{
	if (size == 2)
		write(1, "", 1);
	else if (size == 3 && cmnd)
		printf("%s", cmnd->value);
	else if (size > 3)
	{
		while (cmnd)
		{
			if (cmnd->type == TOKEN_WORD && \
				(!cmnd->prev || !redir_token(cmnd->prev)))
			{
				printf("%s", cmnd->value);
				if (i < size - 1)
					printf(" ");
			}
			i++;
			cmnd = cmnd->next;
		}
	}
}

int	check_option(t_token **cmnd, int *i)
{
	int	flag;

	flag = 0;
	*cmnd = (*cmnd)->next;
	while (*cmnd)
	{
		if (redir_token(*cmnd) || redir_token((*cmnd)->prev))
		{
			*cmnd = (*cmnd)->next;
			continue ;
		}
		if (!is_option((*cmnd)->value))
			break ;
		flag = 1;
		(*i)++;
		*cmnd = (*cmnd)->next;
	}
	return (flag);
}

void	print_args(t_token	*cmnd, t_env *env)
{
	int	size;
	int	i;

	i = 1;
	size = how_many_args(cmnd);
	if (size > 1 && check_option(&cmnd, &i))
		print_with_option(cmnd, size, i);
	else
		print_no_option(cmnd, size);
	update_status(&env, "0");
}
