/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/04/22 15:39:05 by adechaji         ###   ########.fr       */
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
size_t			ft_strlen(const char *s);
t_token			*tokenize(char *input);
int				quoting_check(const char *input);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
void			freewords(char **res, int i);
int				isbuiltincomm(char *com);
int				displaymeagn(char **input);
int				advsyncatcher(char *input, t_env **env);
int				redir_check(const char *token);
int				itsmisplaced(const char *token);
int				notsupported(const char *token);
void			free_tokens(t_token *tokens);
void			quotes_remove(t_token *token);
t_shell			*fill_cmd(t_token *token);
t_shell			*crt_node(void);
t_token			*copy_token(t_token *src);
void			free_shell(t_shell *head);
int				analyze_in_expand(t_token *tokens, t_env *env);
t_expander		expand_token(char *value, t_env *env, \
int inexp, int after_pipe);
void			expand_var(t_expander *exp);
void			handle_quote(t_expander *exp, char quote);
void			handle_backslash(t_expander *exp);
void			append_str(t_expander *exp, char *str);
void			append_char(t_expander *exp, char c);
void			init_expander(t_expander *exp, char *value, \
t_env *env, int inexp);
t_token			*cpy_till_pipe(t_token **curr);
t_token_type	get_token_type(const char *str);
char			*handle_operator(char **input);
void			process_quote_update(t_quote_context *ctx);
void			process_char(char **input, int *len, t_quote_context *ctx);
char			*expanddoc(char *buff, t_env *env);
char			*remove_doc_qts(char *input);
void			catch_signals(void);
int				doc_handle_valids(char *buff, int *i, t_exp *exp, t_env *env);
int				doc_handle_invalids(char *buff, int *i, t_exp *exp);
int				handle_qst_mark(int *i, t_exp *exp, t_env *env);
int				doc_append_str(char **str, size_t *len, \
size_t *cap, char *value);
int				doc_append_char(char **str, size_t *len, size_t *cap, char c);
void			handle_sigint(int sig);
void			split_and_insert(t_token *curr);
int				checkvalidation(const char *str);
void			handle_dollar_sign(t_expander *exp);
void			char_process(t_expander *exp);
void			expand_tilde(t_expander *exp);
int				can_tilde(t_expander *exp);
void			expprocetoken(t_token *current, t_env *env, int inexp, int dol);
void			chinexpdola(t_token *current, int *inexp, int *dol);
int				whitesonly(char *str);
void			expand_norexp_var_else(t_expander *exp, size_t start);
void			append_norexp_words(t_expander *exp, char *var_val);
void			handle_norexp_digits(t_expander *exp, size_t start);
void			handle_norexp_quotes(t_expander *exp, size_t start);

#endif
