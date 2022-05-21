/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_change_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:59:03 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 15:33:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_obj_prop_sphere(t_sphere *sp, char **cmd)
{
	t_vect3	inter;
	float	finter;

	if (get_prop(cmd, &inter, "pos="))
		sp->pos = inter;
	if (get_fprop(cmd, &finter, "radius="))
		sp->rayon = finter;
}

void	change_obj_prop_plane(t_plane *sp, char **cmd)
{
	t_vect3	inter;

	if (get_prop(cmd, &inter, "pos="))
		sp->pos = inter;
	if (get_prop(cmd, &inter, "dir="))
	{
		sp->v1 = inter;
		sp->v2 = norm_vect(prod_vect(sp->v1, (t_vect3){0.f, 1.f, 0.f}));
		if (sp->v1.x == 0.f && sp->v1.y == 1.f && sp->v1.z == 0.f)
			sp->v2 = norm_vect(prod_vect(sp->v1, (t_vect3){0.f, 0.f, 1.f}));
	}
}

void	change_obj_prop_cylinder(t_cylinder *sp, char **cmd)
{
	t_vect3	inter;
	float	finter;

	if (get_prop(cmd, &inter, "pos="))
		sp->pos = inter;
	if (get_prop(cmd, &inter, "dir="))
	{
		sp->dir = inter;
	}
	if (get_fprop(cmd, &finter, "radius="))
		sp->rayon = finter;
	if (get_fprop(cmd, &finter, "height="))
		sp->hauteur = finter;
	if (sp->hauteur == 0.f)
		sp->hauteur = 0.0001f;
}

void	change_obj_light_l(t_datas *data, int idx, char **cmd)
{
	t_vect3	inter;
	float	finter;

	if (get_prop(cmd, &inter, "pos=") && idx == -1)
		data->scene->l.pos = inter;
	if (get_fprop(cmd, &finter, "ratio=") && idx == -1)
		data->scene->l.ratio = finter;
	if (get_fprop(cmd, &finter, "ratio=") && idx == -2)
		data->scene->l_amb.ratio = finter;
	if (get_prop(cmd, &inter, "color=") && idx == -2)
		data->scene->l_amb.color = inter;
}

void	change_obj_light(t_datas *data, int idx, char **cmd)
{
	t_vect3	inter;
	float	finter;

	if (idx == -3)
	{
		if (get_prop(cmd, &inter, "pos="))
			data->scene->cam.pos = inter;
		if (get_prop(cmd, &inter, "dir="))
		{
			data->scene->cam.dir = inter;
			data->scene->cam_right = norm_vect(prod_vect(data->scene->cam.dir, \
	(t_vect3){0.f, -1.f, 0.f}));
			if (data->scene->cam.dir.x == 0.f && fabsf(\
data->scene->cam.dir.y) == 1.f && data->scene->cam.dir.z == 0.f)
				data->scene->cam_right = norm_vect(prod_vect(\
data->scene->cam.dir, (t_vect3){1.f, 0.f, 0.f}));
			data->scene->cam_up = norm_vect(prod_vect(data->scene->cam.dir, \
data->scene->cam_right));
		}
		if (get_fprop(cmd, &finter, "fov="))
			data->fov = deg_to_rad(finter);
	}
	else if (idx == -1 || idx == -2)
		change_obj_light_l(data, idx, cmd);
}
