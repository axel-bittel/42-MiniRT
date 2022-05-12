/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:56:48 by abittel           #+#    #+#             */
/*   Updated: 2021/10/23 15:35:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i = i + 1;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	int		size;
	char	*res;

	i = (size_t)start;
	size = len;
	if (ft_strlen(s) < len)
		size = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res || !s)
		return (NULL);
	if ((unsigned int )ft_strlen(s) < start || !len)
	{
		res[0] = 0;
		return (res);
	}
	while (i - (size_t)start < len && s[i])
	{
		res[i - (size_t)start] = s[i];
		i++;
	}
	res[i - (size_t)start] = 0;
	return (res);
}
