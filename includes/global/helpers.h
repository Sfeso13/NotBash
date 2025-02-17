/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:21:29 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/17 11:59:04 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
t_shell	*ft_lstlast(t_shell *lst);
void	*ft_memcpy(void *dest, const void *src, size_t num);
char	**ft_split(char const *s);
int		nonvalidtoken(char *token);
int		isspecial(char c);
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

#endif