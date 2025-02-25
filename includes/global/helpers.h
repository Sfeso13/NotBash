/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:21:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/25 18:15:39 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
t_shell	*ft_lstlast(t_shell *lst);
void	*ft_memcpy(void *dest, const void *src, size_t num);
char	**ft_split(char const *s);
int		iss_pecial(char c);
int		isquote(char c);
int		iswhitespace(int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		arr_len(char **arr);
int		env_size(t_env *lst);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(const char *s1, const char *s2);
void	free_tab(char **arr);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);
char	*ft_strndup(const char *s, int n);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_strcpy(char *dest, char *src);
char	*get_env_value(char *key, t_env *env);
void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);
t_token	*search_token(t_token *token, t_token_type type);


//list clearing
void	clear_env(t_env **lst, void (*del)(void*));
void	delone_env(t_env **head, t_env *lst, void (*del)(void*));
void	clear_tokens(t_token **lst, void (*del)(void*));
void	delone_token(t_token **head, t_token *lst, void (*del)(void*));
void	clear_shell(t_shell **lst, void (*del)(void*));
void	delone_shell(t_shell **head, t_shell *lst, void (*del)(void*));

#endif
