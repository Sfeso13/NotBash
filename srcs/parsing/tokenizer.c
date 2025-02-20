/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:03:33 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/19 18:59:27 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

// char	**tokenizer(char *input)
// {
// 	char	**tokens;
// 	char	**new_tokens;
// 	char	quote;
// 	int		capacity;
// 	int		st;
// 	int		j;
// 	int		i;
// 	int		k;

// 	capacity = 64;
// 	tokens = malloc(sizeof(char *) * capacity);
// 	if (!tokens)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (input[i])
// 	{
// 		while (iswhitespace(input[i]))
// 			i++;
// 		if (!input[i])
// 			break ;
// 		if (j >= capacity - 1)
// 		{
// 			capacity *= 2;
// 			new_tokens = malloc(sizeof(char *) * capacity);
// 			if (!new_tokens)
// 				return (free_double(tokens), NULL);
// 			k = 0;
// 			while (k < j)
// 			{
// 				new_tokens[k] = tokens[k];
// 				k++;
// 			}
// 			free(tokens);
// 			tokens = new_tokens;
// 		}
// 		// free_double(new_tokens);
// 		if (isquote(input[i]))
// 		{
// 			quote = input[i++];
// 			st = i;
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			tokens[j] = malloc(i - st + 1);
// 			if (!tokens[j])
// 				return (free_double(tokens), NULL);
// 			ft_strncpy(tokens[j], input + st, i - st);
// 			tokens[j][i - st] = '\0';
// 			j++;
// 			i++;
// 		}
// 		else if (isspecial(input[i]))
// 		{
// 			tokens[j] = malloc(3);
// 			if (!tokens[j])
// 				return (free_double(tokens), NULL);
// 			if ((input[i] == '>' && input[i + 1] == '>') ||
// 				(input[i] == '<' && input[i + 1] == '<'))
// 			{
// 				tokens[j][0] = input[i];
// 				tokens[j][1] = input[i + 1];
// 				tokens[j][2] = '\0';
// 				i += 2;
// 			}
// 			else
// 			{
// 				tokens[j][0] = input[i];
// 				tokens[j][1] = '\0';
// 				i++;
// 			}
// 			j++;
// 		}
// 		else
// 		{
// 		st = i;
// 			while (input[i] && !iswhitespace(input[i]) && !isspecial(input[i]))
// 				i++;
// 			tokens[j] = malloc(i - st + 1);
// 			if (!tokens[j])
// 				return (free_double(tokens), NULL);
// 			ft_strncpy(tokens[j], input + st, i - st);
// 			tokens[j][i - st] = '\0';
// 			j++;
// 		}
// 	}
// 	tokens[j] = NULL;
// 	return (tokens);
// }
