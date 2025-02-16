/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:04:16 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 13:26:04 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	char			*key; //the name of the env var
	char			*val; //the value of the env var
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

#endif 