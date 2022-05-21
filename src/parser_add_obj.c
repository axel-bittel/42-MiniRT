/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:02:18 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 11:47:37 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parser_add_l(t_datas *data, char **line_spl)
{
	data->scene->l.pos = read_vect(line_spl[1], data);
	data->scene->l.ratio = ft_atof(line_spl[2]);
	if (line_spl[3])
		data->scene->l.color = read_vect(line_spl[3], data);
	if (data->scene->l.ratio > 1.f || data->scene->l.ratio < 0.f || \
!is_good_color(data->scene->l.color, data))
		print_error(data, ERR_DATA);
	data->scene->l.intensity = 500000000.f / 255.f;
	data->scene->l_amb.is_ambiante = 0;
	return (1);
}

int	parser_add_c(t_datas *data, char **line_spl)
{
	data->scene->cam.pos = read_vect(line_spl[1], data);
	data->scene->cam.dir = read_vect(line_spl[2], data);
	data->fov = (ft_atof(line_spl[3]) * M_PI) / 180;
	if (!is_good_dir(data->scene->cam.dir, data) || data->fov * 180 / M_PI > \
180.f || data->fov * 180 / M_PI < 0.f)
		print_error(data, ERR_DATA);
	data->scene->cam_right = norm_vect(prod_vect(data->scene->cam.dir, \
	(t_vect3){0.f, -1.f, 0.f}));
	if (data->scene->cam.dir.x == 0.f && data->scene->cam.dir.y == -1.f && \
data->scene->cam.dir.z == 0.f)
		data->scene->cam_right = norm_vect(prod_vect(data->scene->cam.dir, \
	(t_vect3){1.f, 0.f, 0.f}));
	data->scene->cam_up = norm_vect(prod_vect(data->scene->cam.dir, \
data->scene->cam_right));
	return (1);
}

int	parser_add_sp(t_datas *data, char **line_spl)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	res->type = TYPE_SPHERE;
	res->obj = malloc(sizeof(t_sphere));
	((t_sphere *)res->obj)->pos = read_vect(line_spl[1], data);
	((t_sphere *)res->obj)->rayon = ft_atof(line_spl[2]);
	res->color = read_vect(line_spl[3], data);
	if (!is_good_color(res->color, data) || ((t_sphere *)res->obj)->rayon < 0)
		print_error(data, ERR_DATA);
	data->scene->objs = add_tab_obj(data->scene->objs, res);
	return (1);
}

int	parser_add_pl(t_datas *data, char **line_spl)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	res->type = TYPE_PLANE;
	res->obj = malloc(sizeof(t_plane));
	((t_plane *)res->obj)->pos = read_vect(line_spl[1], data);
	((t_plane *)res->obj)->v1 = read_vect(line_spl[2], data);
	((t_plane *)res->obj)->v2 = norm_vect(prod_vect(((t_plane *)res->obj)->v1, \
	(t_vect3){0.f, 1.f, 0.f}));
	if (((t_plane *)res->obj)->v1.x == 0.f && ((t_plane *)res->obj)->v1.y \
	== 1.f && ((t_plane *)res->obj)->v1.z == 0.f)
		((t_plane *)res->obj)->v2 = norm_vect(prod_vect(((t_plane *)res->\
	obj)->v1, (t_vect3){0.f, 0.f, 1.f}));
	res->color = read_vect(line_spl[3], data);
	if (!is_good_color(res->color, data) || !is_good_dir(((t_plane *)res->\
	obj)->v1, data))
		print_error(data, ERR_DATA);
	data->scene->objs = add_tab_obj(data->scene->objs, res);
	return (1);
}

int	parser_add_cy(t_datas *data, char **line_spl)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	res->type = TYPE_CYLINDER;
	res->obj = malloc(sizeof(t_cylinder));
	((t_cylinder *)res->obj)->pos = read_vect(line_spl[1], data);
	((t_cylinder *)res->obj)->dir = read_vect(line_spl[2], data);
	((t_cylinder *)res->obj)->rayon = ft_atof(line_spl[3]);
	((t_cylinder *)res->obj)->hauteur = ft_atof(line_spl[4]);
	if (((t_cylinder *)res->obj)->hauteur == 0.0f)
		((t_cylinder *)res->obj)->hauteur = 0.0001f;
	res->color = read_vect(line_spl[5], data);
	if (!is_good_color(res->color, data) || \
!is_good_dir(((t_cylinder *)res->obj)->dir, data) || \
	((t_cylinder *)res->obj)->rayon < 0.f || \
	((t_cylinder *)res->obj)->hauteur < 0.f)
		print_error(data, ERR_DATA);
	data->scene->objs = add_tab_obj(data->scene->objs, res);
	return (1);
}
