/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:52 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/15 17:52:58 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

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


//parsing
t_shell	*inparse(char *input);
int		tokenpars(int *i, char **tokens, t_shell *cmd);
int		is_redirection(char *token);
int		redir_isgood(int *i, char **tokens, t_shell *cmd);
int		is_pipe(char *token);
int		pipe_isgood(t_shell *cmd);
int		tokenpars(int *i, char **tokens, t_shell *cmd);
int		arg_isgood(int *i, char **tokens, t_shell *cmd);
int		checkpipes(char **tokens);
int		emptycomm(char **tokens);
int		quoting_check(char *input);
char	**tokenizer(char *input);

//helpers
char	**ft_old_split(char const *s, char c);
char	**ft_split(char const *s);
int		iswhitespace(int c);
t_shell	*cmd_create(void);
void	cmd_add(t_shell	**head, t_shell *newcmd);
t_shell	*ft_lstlast(t_shell *lst);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
void	free_cmd(t_shell *cmd);
void	free_double(char **dbl);
void	*ft_memcpy(void *dest, const void *src, size_t num);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	freewords(char **res, int i);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		isquote(char c);
int		isspecial(char c);
int		nonvalidtoken(char *token);


#endif