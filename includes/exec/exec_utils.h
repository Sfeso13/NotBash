/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:38:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/18 11:01:41 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		improved_cmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	free_tab(char **arr);
void	envadd_back(t_env **lst, t_env *new);
t_env	*findlast_env(t_env *lst);
t_env	*newenv(char *key, char *value);
t_env	*dup_env(t_env *env);
void	reset_env(t_env **env);
size_t	kv_len(t_env *env);
t_env	*get_smallest_k(t_env *env);

#endif