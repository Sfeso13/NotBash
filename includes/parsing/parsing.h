/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/18 17:32:06 by adechaji         ###   ########.fr       */
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
t_shell	*inparse(char *input);
int		tokenpars(int *i, char **tokens, t_shell *cmd);
int		is_redirection(char *token);
int		redir_isgood(int *i, char **tokens, t_shell *cmd);
int		is_pipe(char *token);
int		tokenpars(int *i, char **tokens, t_shell *cmd);
int		arg_isgood(int *i, char **tokens, t_shell *cmd);
int		checkpipes(char **tokens);
int		emptycomm(char **tokens);
int		quoting_check(const char *input);
char	**tokenizer(char *input);
void	expantions(t_shell *cmd);
char	*expand_it(char *token);
t_shell	*cmd_create(void);
void	cmd_add(t_shell	**head, t_shell *newcmd);
void	free_cmd(t_shell *cmd);
void	free_double(char **dbl);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	freewords(char **res, int i);
int     isbuiltincomm(char *com);
int     displaymeagn(char **input);
int     advsyncatcher(char *input);
int	    redir_check(const char *token);
int     itsmisplaced(const char *token);
int     notsupported(const char *token);

#endif
