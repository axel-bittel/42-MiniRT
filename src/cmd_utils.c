/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:07:34 by abittel           #+#    #+#             */
/*   Updated: 2022/04/20 16:59:30 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include <math.h>
#include <unistd.h>

float	ft_atof(char *s)
{
	int		i;
	int		neg;
	int		is_float;
	float	res;

	i = -1;
	res = 0.0f;
	neg = 1;
	is_float = 0;
	while (s[++i] && s[i] != ',')
	{
		if (s[i] == '-')
			neg = -1;
		else if (ft_isdigit(s[i]) && !is_float)
			res = res * 10 + (s[i] - 48);
		else if (ft_isdigit(s[i]) && is_float)
			res = res + powf(10, -(is_float++)) * (s[i] - 48);
		if (s[i] == '.')
			is_float = 1;
	}
	return (res * neg);
}

char	*mini_gnl(int fd)
{
	char	*res;
	char	*inter;
	int		nb_read;

	res = 0;
	inter = malloc (sizeof(char) * 2);
	nb_read = read(fd, inter, 1);
	while (nb_read)
	{
		inter[1] = 0;
		if (inter[0] == '\n')
		{
			if (!res)
				return (free(inter), res = malloc(1), res[0] = 0, res);
			return (free(inter), res);
		}
		res = ft_strjoin(res, inter);
		nb_read = read(fd, inter, 1);
	}
	free(inter);
	return (res);
}
