/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:57:16 by adechaji          #+#    #+#             */
/*   Updated: 2025/03/07 23:53:00 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../exec/exec.h"
# include "../exec/exec_utils.h"
# include "../parsing/parsing.h"
# include "helpers.h"
# include "structs.h"

//dyalhom
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

volatile sig_atomic_t g_signal_received;

#endif
