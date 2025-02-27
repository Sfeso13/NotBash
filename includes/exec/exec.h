/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/27 14:53:20 by yhossni          ###   ########.fr       */
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

void	external_cmd(t_token *cmnd, t_env *env);
int		is_redirect(t_token *cmnd);

void	ft_dup(int from, int to);

void	run_command(char *path, char **args, t_env *env);

int	redir_token(t_token *cmnd);
void	closefds(int *fd, t_fd fds);

void	piped_exec(t_shell *cmnds, int *fd, t_fd fds, t_env *env);
void	change_fd(int *tochange, int toset, int toclose);
t_fd	init_fd_struct();
void	set_fds(t_fd *fds, int *fd, int process_count, int i);


void	restore_stds(int saved_in, int saved_out);

//heredoc
char	*join_name(char *name, int *i);
char	*get_filename(void);
char	*read_input(int expandable, char *delim, int fd, t_env *env);
int	get_doc(char *delim, t_env *env);


//io preparing
int	how_many_redir(t_token *cmnd, t_token_type type);
// int	*init_fds();
int	*get_io_files(t_token *args, t_env *env);
//utils
int	check_doc_limit(int count);
int	handleinput(t_token *tmp, int *fd, t_redir redir, t_env *env);
int	handleoutput(t_token *tmp, int *fd, t_redir redir);
t_redir	init_redir_struct(t_token *args);
void	exec_builtins(t_shell *shell, t_token *cmnd, t_env *env);
void	redir_exec(t_fd fds);

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
int	*init_fds(void);
int	fdop(int to_open, int append, char *filename, int write);
int	what_in_to_open(t_token *tmp, int fd, int *inredir, t_env *env);
int	what_out_to_open(t_token *tmp, int fd, int *outredir);
int	get_doc(char *delim, t_env *env);

#endif
