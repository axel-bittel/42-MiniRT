/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:55:55 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 15:34:52 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*create_new_plane(char **str)
{
	t_plane	*res;
	t_vect3	inter;

	res = malloc(sizeof(t_plane));
	res->pos = (get_prop(str, &inter, "pos="), inter);
	res->v1 = (get_prop(str, &inter, "dir="), inter);
	res->v2 = norm_vect(prod_vect(res->v1, (t_vect3){0.f, 1.f, 0.f}));
	if (res->v1.x == 0.f && res->v1.y == 1.f && res->v1.z == 0.f)
		res->v2 = norm_vect(prod_vect(res->v1, (t_vect3){0.f, 0.f, 1.f}));
	return ((void *)res);
}

void	*create_new_sphere(char **str)
{
	t_sphere	*res;
	t_vect3		inter;
	float		finter;

	res = malloc(sizeof(t_sphere));
	res->pos = (get_prop(str, &inter, "pos="), inter);
	res->rayon = (get_fprop(str, &finter, "radius="), finter);
	return ((void *)res);
}

void	*create_new_cylinder(char **str)
{
	t_cylinder	*res;
	t_vect3		inter;
	float		finter;

	res = malloc(sizeof(t_cylinder));
	res->pos = (get_prop(str, &inter, "pos="), inter);
	res->dir = (get_prop(str, &inter, "dir="), inter);
	res->rayon = (get_fprop(str, &finter, "radius="), finter);
	res->hauteur = (get_fprop(str, &finter, "height="), finter);
	return ((void *)res);
}
