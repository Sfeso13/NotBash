/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 14:50:00 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../global/structs.h"
# include "../global/minishell.h"
# include <limits.h>

int		improved_cmp(const char *s1, const char *s2);
void	execute(t_shell *cmnds, t_env *env);
void	export_env(t_shell *cmnds, t_env *env);
t_env	*get_smallest_k(t_env *env);
void	unset_var(t_shell *cmnds, t_env *env);
void    print_current_dir();
void    changedir();

#endif