/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:52:51 by abittel           #+#    #+#             */
/*   Updated: 2021/10/24 12:05:26 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	conv_s1;
	unsigned char	conv_s2;

	i = 0;
	conv_s1 = (unsigned char)s1[i];
	conv_s2 = (unsigned char)s2[i];
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		conv_s1 = (unsigned char)s1[i];
		conv_s2 = (unsigned char)s2[i];
		if (conv_s1 != conv_s2)
			return (conv_s1 - conv_s2);
		i = i + 1;
	}
	if ((!s1[i] || !s2[i]) && i != n)
	{
		conv_s1 = (unsigned char)s1[i];
		conv_s2 = (unsigned char)s2[i];
	}
	return (conv_s1 - conv_s2);
}
