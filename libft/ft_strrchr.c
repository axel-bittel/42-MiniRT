/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:28:37 by abittel           #+#    #+#             */
/*   Updated: 2021/08/06 02:08:05 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stddef.h>

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i = i + 1;
	return (i);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (((unsigned char *)s)[i + 1] == (unsigned char)c)
		return (s + i + 1);
	while (i >= 0)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (s + i);
		i = i - 1;
	}
	return (NULL);
}
