/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 16:49:25 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../global/structs.h"
# include <stdio.h>
# include <stdlib.h>
# include "builtins.h"
# include "exec_utils.h"

typedef struct s_shell t_shell;

int		improved_cmp(const char *s1, const char *s2);
void	execute(t_shell *cmnds, t_env *env);

#endif