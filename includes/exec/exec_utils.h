/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:38:03 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 10:47:43 by yhossni          ###   ########.fr       */
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
// size_t	kv_len(t_env *env);
// t_env	*get_smallest_k(t_env *env);
char	**kv_extract(char *var);
// void	copy_kv(char *str, t_env *min, size_t len);
// t_env	*search_key(char *key, t_env *env);
// void	change_value_of_key(t_env **tochange, char *value);

//key validation
// char	*validate_key(char *key);
// int		is_plus(char *s);
// int		allowed(char *c);
// char	*unset_validate_key(char *key);
// int	unset_allowed(char *c);

// export var
// int		handle_keys(t_env **env, char **kv, char *equal);
// int		handle_append(t_env **env, char **kv);
// char	**export_kv_extract(char *var);
// int		how_many_args(t_token *cmnd);

//print export
// char	**env_to_arr(t_env *env);
// void	print_full_env(t_env *env);

#endif
