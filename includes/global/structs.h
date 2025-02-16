/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:29:31 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/16 23:55:03 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key; //the name of the env var
	char			*val; //the value of the env var
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	char			**args;			// array of commands + args || (["ls", "-l", NULL])
	char			*infile;		// file input redirection   (< file.txt)
	char			*outfile;		// file output redirection   (< file.txt)
	int				append_mode;	// flag append mode (>> file.txt)
	char			*heredoc_dlm;	// heredoc delimiter (<< delim)
	struct s_shell	*next;			// ptr to the next command in the pipeline
	struct s_shell	*prev;			// ptr to the previous command in the pipeline
}	t_shell;

// typedef struct s_token
// {
// 	char	**value;
// 	char	quote;
// }	t_token;

#endif