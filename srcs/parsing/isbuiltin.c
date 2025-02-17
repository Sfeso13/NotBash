/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:51 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/17 16:09:35 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

int isbuiltincomm(char *com)
{
    const char *builtins[] = {"echo", "cd", "export", "unset", "env", "exit", NULL};
    int         i;

    i = 0;
    if (!com)
        return (0);
    while (builtins[i])
    {
        if (ft_strcmp(com, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

