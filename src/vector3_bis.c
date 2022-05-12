/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:27:15 by abittel           #+#    #+#             */
/*   Updated: 2022/05/07 23:37:31 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_vect3	prod_vect(t_vect3 v1, t_vect3 v2)
{
	t_vect3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

float	dot_product(t_vect3 v1, t_vect3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	add_vect3(t_vect3 *v, int coord, int size)
{
	int		i;
	float	res;

	res = 0.f;
	i = -1;
	while (++i < size)
	{
		if (coord == 1)
			res += v[i].x;
		else if (coord == 2)
			res += v[i].y;
		else if (coord == 3)
			res += v[i].z;
	}
	return (res);
}
