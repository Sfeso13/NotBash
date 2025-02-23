/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/23 12:53:53 by yhossni          ###   ########.fr       */
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

int		improved_cmp(const char *s1, const char *s2);
void	execute(t_shell *cmnds, t_env *env);

//io preparing
int	how_many_redir(t_token *cmnd, t_token_type type);
int	*init_fds();
int	*get_io_files(t_token *args);

//args preparing
char	*get_cmnd_path(t_token *cmnd, t_env *env);
char	**prepare_args(t_token *cmnd);

//args helper
void	copy_kv(char *str, t_env *env, size_t len);
char	**env_to_arr(t_env *env);
char	*join(char const *s1, char const *s2);
char	**args_split(char const *s, char c);

#endif
