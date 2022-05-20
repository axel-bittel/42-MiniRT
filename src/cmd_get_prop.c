/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_prop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:55:12 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 20:01:26 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_vect_cond(char *str, t_vect3 *res, int *coord, int *i)
{
	if (*coord == 0)
		res->x = ft_atof(str + *i);
	if (*coord == 1)
		res->y = ft_atof(str + *i);
	else if (*coord == 2)
	{
		res->z = ft_atof(str + *i);
		(*coord)++;
		return (1);
	}
	(*coord)++;
	while (str[*i + 1] && str[*i + 1] != ',')
		(*i)++;
	return (0);
}

int	get_vect(char *str, t_vect3 *res)
{
	int	i;
	int	coord;

	i = -1;
	coord = 0;
	while (str[++i])
		if ((ft_isdigit(str[i]) || str[i] == '-'))
			if (get_vect_cond(str, res, &coord, &i))
				break ;
	if (coord != 3)
	{
		print_cmd_error(ERR_VECTOR);
		return (0);
	}
	else
		return (1);
}

int	get_prop(char **str, t_vect3 *v, char *prop)
{
	int		i;
	t_vect3	inter;

	i = -1;
	*v = (t_vect3){0.f, 0.f, 0.f};
	while (str[++i])
	{
		if (!ft_strncmp(str[i], prop, ft_strlen(prop)))
		{
			if (get_vect(str[i] + ft_strlen(prop), &inter))
			{
				*v = inter;
				return (1);
			}
		}
	}
	return (0);
}

int	get_fprop(char **str, float *f, char *prop)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], prop, ft_strlen(prop)))
		{
			*f = ft_atof(str[i] + ft_strlen(prop));
			return (1);
		}
	}
	return (0);
}
