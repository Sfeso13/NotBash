/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/22 01:46:53 by adechaji         ###   ########.fr       */
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
size_t	get_var_length(const char **str);
size_t	calculate_buf_size(const char *token);
t_shell	*fill_cmd(t_token *token);
t_shell	*crt_node(void);
t_token	*copy_token(t_token *src);
void	free_shell(t_shell *head);
void	analyze_in_expand(t_token *tokens, t_env *env);
char	*expand_token(char *value, t_env *env);
void	expand_var(t_expander *exp);
void	handle_quote(t_expander *exp, char quote);
void	handle_backslash(t_expander *exp);
void	append_str(t_expander *exp, char *str);
void	append_char(t_expander *exp, char c);
void	init_expander(t_expander *exp, char *value, t_env *env);

#endif
