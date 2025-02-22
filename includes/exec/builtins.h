/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:29:45 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/22 11:02:00 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../exec/builtins_utils.h"

//env
void	print_env(t_env *env);

//export
void	export_env(t_token *cmnd, t_env *env);
void	export_var(t_token *cmnd, t_env **env, int args_size);
void	print_full_env(t_env *env);

//unset
void	unset_var(t_token *cmnd, t_env *env);

//exit
void	exit_shell(t_shell **shell, t_token **cmnd, t_env **env);
int		validate_status(char *status);

//cd
void	changedir(t_token *cmnd, t_env *env);

//echo
void	print_args(t_token	*cmnd);
void	print_with_option(t_token *cmnd, int size);
void	print_no_option(t_token *cmnd, int size);

//pwd
void	print_current_dir(t_env *env);

#endif
