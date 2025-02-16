/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splithelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:51:19 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 16:28:12 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/helpers.h"

int	iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\v');
}

int	isquote(char c)
{
	return (c == '"' || c == '\'');
}

int	isspecial(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	nonvalidtoken(char *token)
{

	return (/*ft_strncmp(token, ";", 1) == 0 || */ft_strncmp(token, "&", 1) == 0 || ft_strncmp(token, "*", 1) == 0);
}
