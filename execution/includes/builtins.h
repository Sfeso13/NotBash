/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:45 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 11:36:58 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "exec.h"

void	envadd_back(t_env **lst, t_env *new);
t_env	*newenv(char *key, char *value);
t_env	*create_env(char *env[]);
t_env	*findlast_env(t_env *lst);

#endif