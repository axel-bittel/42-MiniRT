/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:04:58 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/21 14:21:21 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char a, char *sep)
{
	int	i;

	i = 0;
	if (!sep)
		return (0);
	while (sep[i])
	{
		if (a == sep[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_wordcount(char *str, char *charset)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	j = 0;
	w = 0;
	while (str[i] && str[j])
	{
		i = j;
		while (is_sep(str[i], charset) && str[i])
		{
			if (str[i + 1] == 0)
				w--;
			i++;
		}
		j = i;
		while (!is_sep(str[j], charset) && str[j])
			j++;
		w++;
	}
	return (w);
}

char	**ft_wordalloc(char *str, char *charset)
{
	int		i;
	int		j;
	int		w;
	char	**tabst;

	w = 0;
	i = 0;
	j = 0;
	tabst = ft_calloc(ft_wordcount(str, charset) + 2, sizeof(char *));
	if (!tabst)
		return (NULL);
	while (str[i] && str[j])
	{
		i = j;
		while (is_sep(str[i], charset) && str[i])
			i++;
		j = i;
		while (!is_sep(str[j], charset) && str[j])
			j++;
		tabst[w] = ft_calloc((j - i) + 1, sizeof(char));
		w++;
	}
	tabst[w] = NULL;
	return (tabst);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		k;
	int		j;
	char	**dest;

	k = 0;
	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	dest = ft_wordalloc(str, charset);
	if (!dest)
		return (NULL);
	while (j < ft_wordcount(str, charset))
	{
		k = 0;
		while (is_sep(str[i], charset) && str[i])
			i++;
		while (!is_sep(str[i], charset) && str[i])
			dest[j][k++] = str[i++];
		dest[j][k] = 0;
		j++;
	}
	return (dest);
}
