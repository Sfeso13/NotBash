/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:14 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 15:14:28 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include "builtins.h"

typedef struct s_shell t_shell;

int		improved_cmp(const char *s1, const char *s2);
void	execute(t_shell *cmnds, t_env *env);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif