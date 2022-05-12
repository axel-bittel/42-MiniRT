/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:11:26 by abittel           #+#    #+#             */
/*   Updated: 2021/10/22 16:16:36 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i = i + 1;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = s[i];
		i = i + 1;
	}
	res[i] = 0;
	return (res);
}
