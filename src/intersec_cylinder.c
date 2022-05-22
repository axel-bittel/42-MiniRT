/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:02:43 by abittel           #+#    #+#             */
/*   Updated: 2022/05/22 12:31:02 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_int_cy_d(t_ray dir, float *inter, t_cylinder c, int up)
{
	t_vect3	inter_inter;
	t_vect3	inter_norm;
	t_vect3	plan_point;
	float	intersec;

	if (!up)
		up = -1;
	inter_norm = norm_vect(mult_scal(norm_vect(c.dir), up));
	plan_point = add_vects(mult_scal(mult_scal(norm_vect(c.dir), c.hauteur / \
2.f), up), c.pos);
	if (fabsf(dot_product(dir.dir, inter_norm)) > 0.00000001f)
	{
		intersec = dot_product(diff_vects(plan_point, dir.pos), inter_norm) / \
dot_product(dir.dir, inter_norm);
		if (intersec < 0.f)
			return (0);
		inter_inter = add_vects(dir.pos, mult_scal(dir.dir, intersec));
		if (norm_square(diff_vects(inter_inter, plan_point)) < powf(c.rayon, 2))
		{
			*inter = intersec;
			return (1);
		}
	}
	return (0);
}

int	is_intersection_body_sols(t_ray new_dir, t_cylinder c, \
float *t_one, float *t_two)
{
	float	a;
	float	b;
	float	c_eq;
	t_vect3	inter;

	inter = prod_vect(new_dir.dir, c.dir);
	a = norm_square(inter);
	inter = prod_vect(diff_vects(new_dir.pos, c.pos), c.dir);
	b = 2.f * dot_product(prod_vect(new_dir.dir, c.dir), inter);
	c_eq = norm_square(inter) - (c.rayon * c.rayon * norm_square(c.dir));
	if (b * b - 4.f * a * c_eq < 0.f || c.rayon == 0.f)
		return (0);
	*t_one = (-b - sqrtf(b * b - 4.f * a * c_eq)) / (2.f * a);
	*t_two = (-b + sqrtf(b * b - 4.f * a * c_eq)) / (2.f * a);
	if (*t_one < 0.f && *t_two < 0.f)
		return (0);
	return (1);
}

int	is_int_bd_cy(t_ray new_dir, t_cylinder c, float *inter)
{
	float	t_one;
	float	t_two;
	t_vect3	inter_one;
	t_vect3	inter_two;

	if (!is_intersection_body_sols(new_dir, c, &t_one, &t_two) \
	|| c.rayon == 0.f || c.hauteur == 0.f)
		return (0);
	inter_one = mult_scal(add_vects(mult_scal(new_dir.dir, t_one), \
new_dir.pos), (t_one > 0.f));
	inter_two = mult_scal(add_vects(mult_scal(new_dir.dir, t_two), \
new_dir.pos), (t_two > 0.f));
	if (sqrtf(norm_square(mult_scal(norm_vect(c.dir), dot_product(diff_vects(\
	inter_one, c.pos), norm_vect(c.dir))))) > c.hauteur / 2.f || t_one < 0.f)
	{
		if (sqrtf(norm_square(mult_scal(norm_vect(c.dir), dot_product(\
		diff_vects(inter_two, c.pos), norm_vect(c.dir))))) > c.hauteur / 2.f)
			return (0);
		*inter = t_two;
	}
	else if (t_one > 0.f)
		*inter = t_one;
	return (1);
}

void	get_norm_cylinder(int is_disque, t_cylinder c, \
t_vect3 *inter, t_vect3 *norm)
{
	int	is_disque_val;

	is_disque_val = 0;
	if (is_disque & 16)
		is_disque_val = -1;
	if (is_disque & 8)
		is_disque_val = 1;
	if (is_disque & 32)
		is_disque_val *= -1;
	if (is_disque_val)
		*norm = norm_vect(mult_scal(c.dir, is_disque_val));
	else
		*norm = norm_vect(diff_vects(diff_vects(*inter, c.pos), mult_scal(\
norm_vect(c.dir), dot_product(diff_vects(*inter, c.pos), norm_vect(c.dir)))));
}

int	is_intersection_cylinder(t_ray new_dir, t_cylinder c, \
t_vect3 *inter, t_vect3 *norm)
{
	float	inter_body;
	float	inter_d_up;
	float	inter_d_down;
	int		is_int;

	is_int = is_int_bd_cy(new_dir, c, &inter_body) + is_int_cy_d(new_dir, \
&inter_d_up, c, 1) * 2 + is_int_cy_d(new_dir, &inter_d_down, c, 0) * 4;
	if (!(is_int & 1) + !(is_int & 2) + !(is_int & 4) == 3 || is_null(&c.dir))
		return (0);
	*inter = add_vects(mult_scal(new_dir.dir, inter_body), new_dir.pos);
	if ((is_int & 4) && (inter_d_down < inter_body || !(is_int & 1)) && \
	(!(is_int & 2) || inter_d_down < inter_d_up))
	{
		*inter = add_vects(mult_scal(new_dir.dir, inter_d_down), new_dir.pos);
		is_int += 16;
	}
	if ((is_int & 2) && (inter_d_up < inter_body || !(is_int & 1)) && \
	(!(is_int & 4) || inter_d_up < inter_d_down))
	{
		*inter = add_vects(mult_scal(new_dir.dir, inter_d_up), new_dir.pos);
		is_int += 8;
	}
	if (dot_product(new_dir.dir, mult_scal(c.dir, 1 + (is_int & 16) * -2)) > 0)
		is_int += 32;
	return (get_norm_cylinder(is_int, c, inter, norm), 1);
}
