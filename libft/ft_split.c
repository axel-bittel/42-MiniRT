/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:55:27 by abittel           #+#    #+#             */
/*   Updated: 2021/11/02 11:53:49 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static int	nb_words(char const *s, char c)
{
	int	i;
	int	res;
	int	is_in_w;

	i = 0;
	res = 0;
	is_in_w = 0;
	while (s[i])
	{
		if (s[i] != c)
			is_in_w = 1;
		else
		{
			if (is_in_w)
				res++;
			is_in_w = 0;
		}
		i = i + 1;
	}
	if (i && s[i - 1] != c)
		res += 1;
	return (res);
}

static int	size_w(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && *(s++) != c)
		i = i + 1;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	t_args_idx			idx;
	char				**res;

	res = (char **)malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!res)
		return (NULL);
	res[nb_words(s, c)] = NULL;
	idx.i = 0;
	idx.j = 0;
	while (idx.j < nb_words(s, c) && s[idx.i])
	{
		if (s[idx.i] != c)
		{
			idx.k = 0;
			res[idx.j] = malloc(sizeof(char) * (size_w(s + idx.i, c) + 1));
			if (!res[idx.j])
				return (NULL);
			while (s[idx.i] && s[idx.i] != c)
				res[idx.j][idx.k++] = s[idx.i++];
			res[idx.j++][idx.k] = 0;
		}
		idx.i = idx.i + 1;
	}
	return (res);
}
