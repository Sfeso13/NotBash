/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:52:42 by yhossni           #+#    #+#             */
/*   Updated: 2025/02/28 17:36:26 by yhossni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec/exec.h"

char	*join(char const *s1, char const *s2)
{
	char	*str;
	int		lens1;
	int		lens2;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	len = lens1 + lens2 + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, lens1);
	ft_memcpy(str + lens1, " ", 1);
	ft_memcpy(str + lens1 + 1, s2, lens2);
	return (str);
}

void	copy_kv(char *str, t_env *env, size_t len)
{
	size_t	klen;

	klen = ft_strlen(env->key);
	ft_strlcpy(str, env->key, len + 1);
	if (len > klen)
	{
		ft_strlcat(str + klen, "=", len + 1);
		if (env->val)
			ft_strlcat(str + klen + 1, env->val, len + 1);
	}
}

char	**env_to_arr(t_env *env)
{
	char	**copy;
	int		i;
	size_t	len;

	i = 0;
	copy = (char **)malloc((env_size(env) + 1) * sizeof(char *));
	if (!copy)
		return (NULL); //FAILURE
	while (env)
	{
		if (env->key[0] != '.' && env->key[0] != '?')
		{
			len = kv_len(env) - 2;
			copy[i] = (char *)malloc(len + 1); //add safe free
			copy_kv(copy[i], env, len);
			i++;
		}
		env = env->next;
	}
	copy[i] = NULL;
	return (copy);
}

int	redir_token(t_token *cmnd)
{
	if (cmnd->type == TOKEN_REDIRECT_IN || cmnd->type == TOKEN_REDIRECT_OUT || \
		cmnd->type == TOKEN_APPEND || cmnd->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}
