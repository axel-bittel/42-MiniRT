/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:27:48 by abittel           #+#    #+#             */
/*   Updated: 2021/10/29 18:49:18 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	is_trimchar(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_strlen_trim(const char *s, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] && is_trimchar(s[i], (char *)set))
		i++;
	while (j > 0 && is_trimchar(s[j], (char *)set))
		j--;
	return (j - i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*res;

	i = 0;
	j = 0;
	if ((int)ft_strlen_trim(s1, set) <= 0)
	{
		res = (char *)malloc(sizeof(char) * (1));
		res[0] = 0;
		return (res);
	}
	res = (char *)malloc(sizeof(char) * ((int)ft_strlen_trim(s1, set) + 1));
	if (!res)
		return (NULL);
	while (s1[i] && is_trimchar(s1[i], (char *)set))
		i++;
	while (j < ft_strlen_trim(s1, set))
	{
		res[j] = s1[i + j];
		j++;
	}
	res[j] = 0;
	return (res);
}
