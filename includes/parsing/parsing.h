/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/21 01:46:55 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// # include "../global/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//parsing
size_t	ft_strlen(const char *s);
t_token	*tokenize(char *input);
int		quoting_check(const char *input);
void	expantions(t_token *cmd);
char	*expand_it(char *token);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	freewords(char **res, int i);
int		isbuiltincomm(char *com);
int		displaymeagn(char **input);
int		advsyncatcher(char *input);
int		redir_check(const char *token);
int		itsmisplaced(const char *token);
int		notsupported(const char *token);
void	free_tokens(t_token *tokens);
void	quotes_remove(t_token *token);
void	handle_quotes(char c, t_expand *ex);
size_t	get_var_length(const char **str);
void	skip_quotes(const char **p, t_expand *ex);
size_t	calculate_buf_size(const char *token);

#endif
