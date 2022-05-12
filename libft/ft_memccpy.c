/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:35:50 by root              #+#    #+#             */
/*   Updated: 2021/10/21 12:17:38 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int		is_in_chr;
	size_t	i;

	i = 0;
	is_in_chr = 0;
	while (i < n && !is_in_chr)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
			is_in_chr = 1;
		((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
		i = i + 1;
	}
	if (!is_in_chr)
		return (NULL);
	return ((void *)(dest + i));
}
