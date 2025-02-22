/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:38:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 19:35:25 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		improved_cmp(const char *s1, const char *s2);
char	**kv_extract(char *var);
void	set_env_value(t_env **env, char *value);
void	update_dash(t_token *cmnd, t_env **env);
t_token	*extract_cmd(t_token *process);
int		how_many_processes(t_shell *process);

#endif
