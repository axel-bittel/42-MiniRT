/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:48:40 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 11:19:22 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect3	add_vects(t_vect3 v1, t_vect3 v2)
{
	t_vect3	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vect3	diff_vects(t_vect3 v1, t_vect3 v2)
{
	t_vect3	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vect3	mult_scal(t_vect3 v1, float scal)
{
	t_vect3	res;

	res.x = v1.x * scal;
	res.y = v1.y * scal;
	res.z = v1.z * scal;
	return (res);
}

float	norm_square(t_vect3 v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

t_vect3	norm_vect(t_vect3 v1)
{
	t_vect3	res;
	float	norm;

	norm = sqrtf(norm_square(v1));
	res.x = v1.x / norm;
	res.y = v1.y / norm;
	res.z = v1.z / norm;
	return (res);
}
