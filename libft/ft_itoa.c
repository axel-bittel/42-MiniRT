/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 23:26:21 by abittel           #+#    #+#             */
/*   Updated: 2021/08/05 23:43:10 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

/*static void	ft_bzero(void	*s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i = i + 1;
	}
}*/

static int	ft_size_itoa(int nb)
{
	int	i;

	i = 0;
	while (nb)
	{
		nb = nb / 10;
		i = i + 1;
	}
	return (i);
}

static int	ft_itoa_rec(int n, char *str)
{
	char	res;
	int		i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		res = n - ft_itoa_rec(n / 10, str) * 10 + 48;
		while (str[i])
			i = i + 1;
		str[i] = res;
		return (n);
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		is_neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = n * -1;
	}
	res = malloc(sizeof(char) * (ft_size_itoa(n) + 1 + 1 * is_neg));
	if (!res)
		return (NULL);
	ft_bzero(res, (ft_size_itoa(n) + is_neg + 1));
	if (is_neg)
		res[0] = '-';
	ft_itoa_rec(n, res);
	return (res);
}
