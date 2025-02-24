/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/24 18:29:36 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../global/structs.h"
# include "../exec/builtins.h"
# include "../global/minishell.h"
# include <limits.h>
# include <sys/wait.h> //linux
# include <errno.h>

int		improved_cmp(const char *s1, const char *s2);
void	execute(t_shell *cmnds, t_env *env);

void	external_cmd(t_shell *shell, t_token *cmnd, t_env *env);
int		is_redirect(t_token *cmnd);

t_token	*search_token(t_token *token, t_token_type type);

void	ft_dup(int from, int to);

void	run_command(char *path, char **args, t_env *env);

//io preparing
int	how_many_redir(t_token *cmnd, t_token_type type);
int	*init_fds();
int	*get_io_files(t_token *args, t_env *env);

//args preparing
char	*get_cmnd_path(t_token *cmnd, t_env *env);
char	**prepare_args(t_token *cmnd);
void	redirect(t_token *cmnd, t_env *env);

//args helper
void	copy_kv(char *str, t_env *env, size_t len);
char	**env_to_arr(t_env *env);
char	*join(char const *s1, char const *s2);
char	**args_split(char const *s, char c);

//io helpers
int	how_many_redir(t_token *cmnd, t_token_type type);
int	*init_fds();
int	fdop(int to_open, int append, char *filename, int write);
int	what_in_to_open(t_token *tmp, int fd, int *inredir, t_env *env);
int	what_out_to_open(t_token *tmp, int fd, int *outredir);
int	get_doc(char *delim, t_env *env);

#endif
