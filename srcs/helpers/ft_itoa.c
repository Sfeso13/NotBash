/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:09:16 by adechaji          #+#    #+#             */
/*   Updated: 2025/02/16 19:04:07 by adechaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global/minishell.h"

static int	ccountnum(long n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count++;
		return (count);
	}
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	yareversi(char *str)
{
	char	temp;
	int		f ;
	int		len;
	int		l;

	len = ft_strlen(str);
	l = len - 1;
	f = 0;
	while (f < len / 2)
	{
		temp = str[f];
		str[f] = str[l];
		str[l] = temp;
		f++;
		l--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		nlen;
	int		i;
	long	num;

	num = n;
	nlen = ccountnum(num);
	res = ft_calloc(nlen + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (num < 0)
	{
		res[i++] = '-';
		num = -num;
	}
	while (num > 0 || (n == 0 && i == 0))
	{
		res[i++] = (num % 10) + '0';
		num /= 10;
	}
	yareversi(res + (n < 0));
	return (res);
}
