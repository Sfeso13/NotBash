/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:58:51 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/28 19:52:25 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H

# include "../exec/exec.h"

//general utils
int	how_many_args(t_token *cmnd);
int		isbuiltin(char *com);
void	which_builtin(t_shell *shell, t_token *cmnd, t_env **env);
void	update_status(t_env **env, char *status);

//cd utils
char	*get_home_dir(t_env *env);
void	update_pwd(t_env **env);
int		find_pwd_nodes(t_env *env, t_env **actual, t_env **hidden);
int		find_oldpwd_nodes(t_env *env, t_env **actual, t_env **hidden);

//env utils
void	envadd_back(t_env **lst, t_env *new);
char	**env_to_arr_export(t_env *env);
t_env	*newenv(char *key, char *value);
t_env	*dup_env(t_env *env);
void	reset_env(t_env **env);
t_env	*create_env(char *env[]);
t_env	*findlast_env(t_env *lst);
void	create_clean_env(t_env **env);
void	set_env_value(t_env **env, char *value);

//export utils
void	change_value_of_key(t_env **tochange, char *value);
char	*validate_key(char *key);
int		is_plus(char *s);
int		allowed(char *c);
int		handle_keys(t_env **env, char **kv, char *equal);
int		handle_append(t_env **env, char **kv);
char	**export_kv_extract(char *var);
void	copy_kv_export(char *str, t_env *min, size_t len);
t_env	*search_key(char *key, t_env *env);
size_t	kv_len(t_env *env);
t_env	*get_smallest_k(t_env *env);

//unset utils
char	*unset_validate_key(char *key);
int		unset_allowed(char *c);

#endif
