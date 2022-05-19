/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sect_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 01:05:35 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 21:10:32 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_intersection_sphere(t_ray dir, t_sphere s, t_vect3 *inter, t_vect3 *norm)
{
	float	delta;
	float	b;
	float	c;
	float	r1;
	float	r2;

	b = 2.f * dot_product(dir.dir, diff_vects(dir.pos, s.pos));
	c = norm_square(diff_vects(dir.pos, s.pos)) - s.rayon * s.rayon;
	delta = b * b - 4.f * c;
	if (delta < 0.f || s.rayon == 0.f)
		return (0);
	r1 = (-b - sqrtf(delta)) / (2.f);
	r2 = (-b + sqrtf(delta)) / (2.f);
	if (r1 < 0.f && r2 < 0.f)
		return (0);
	if (r1 < r2 && r1 > 0.f)
		*inter = add_vects(dir.pos, mult_scal(dir.dir, r1));
	else
		*inter = add_vects(dir.pos, mult_scal(dir.dir, r2));
	*norm = norm_vect(diff_vects(*inter, s.pos));
	return (1);
}

int	is_intersection_plane(t_ray dir, t_plane p, t_vect3 *inter, t_vect3 *norm)
{
	float	intersec;

	*norm = norm_vect(p.v1);
	if (dot_product(*norm, dir.dir) > 0)
	{
		*norm = mult_scal(*norm, -1);
		return (0);
	}
	if (fabsf(dot_product(dir.dir, *norm)) <= 0.0001f)
		return (0);
	intersec = dot_product(diff_vects(p.pos, dir.pos), p.v1) / \
dot_product(dir.dir, p.v1);
	if (intersec < 0.f)
		return (0);
	*inter = add_vects(dir.pos, mult_scal(dir.dir, intersec));
	return (1);
}

int	is_intersection(t_ray dir, t_obj o, t_vect3 *inter, t_vect3 *norm)
{
	if (o.type == TYPE_SPHERE)
		return (is_intersection_sphere(dir, *(t_sphere *)o.obj, inter, norm));
	if (o.type == TYPE_PLANE)
		return (is_intersection_plane(dir, *(t_plane *)o.obj, inter, norm));
	if (o.type == TYPE_CYLINDER)
		return (is_intersection_cylinder(dir, *(t_cylinder *)o.obj, \
inter, norm));
	return (0);
}
