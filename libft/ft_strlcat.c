/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 11:28:31 by abittel           #+#    #+#             */
/*   Updated: 2021/10/23 11:34:32 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static unsigned int	ft_strlen(char *str)
{
	unsigned int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_dest;
	unsigned int	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen((char *)src);
	i = 0;
	j = 0;
	if (!size || len_dest > size)
		return (len_src + size);
	while (dest[i])
		i++;
	while (src[j] && ((i + j) < size - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (len_src + i);
}
