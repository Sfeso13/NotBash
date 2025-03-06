/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:29:31 by yhossni           #+#    #+#             */
/*   Updated: 2025/03/06 14:32:31 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//past me f google https://knowyourmeme.com/memes/jaking-it-jakeing-it
// fuck the old struct thats all we need :

typedef struct s_redir{
    int	in_count[2];
    int	out_count[2];
	int	docs[16];
	int	doc_pos;
} t_redir;

typedef struct s_fd{
    int infd;
    int outfd;
	int	pfd[2];
} t_fd;

typedef struct	s_exp
{
	char	*res;
	size_t	len;
	size_t	cap;
}	t_exp;

typedef struct	s_quote
{
	int		scc;
	int		dcc;
} t_quote;

typedef struct	s_quote_state
{
	int		in_quotes;
	char	quchar;
} t_quote_state;

typedef struct s_quote_context
{
	t_quote_state	state;
	int				*scc;
	int				*dcc;
}	t_quote_context;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	char			*value;
	//if we wanna add something in futur
	int				expanded;
	int				ambiguous;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key; //the name of the env var
	char			*val; //the value of the env var
	int				is_set;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	t_token			*tokens;
	// char			**args;			// array of commands + args || (["ls", "-l", NULL])
	struct s_shell	*next;			// ptr to the next command in the pipeline
	struct s_shell	*prev;			// ptr to the previous command in the pipeline
}	t_shell;

typedef struct s_expander
{
	const char	*value;
	size_t		i;
	char		*buffer;
	size_t		buf_size;
	size_t		buf_pos;
	t_env		*env;
	int			in_single;
	int			in_double;
	int			escape_next;
	int			expme;
}	t_expander;

#endif
