/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_obj_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:02:18 by abittel           #+#    #+#             */
/*   Updated: 2022/05/16 19:02:01 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "obj.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "parser.h"

int	parser_add_l(t_datas *data, char **line_spl)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	new->pos = read_vect(line_spl[1], data);
	new->ratio = ft_atof(line_spl[2]);
	new->color = read_vect(line_spl[3], data);
	if (new->ratio > 1.f || data->scene->l.ratio < 0.f || \
!is_good_color(data->scene->l.color, data))
		return (free(new), print_error(data), 0);
	new->intensity = 300000000.f / 255.f;
	new->is_ambiante = 0;
	data->scene->l_tab = add_tab_light(data->scene->l_tab, new);
	data->scene->nb_light++;
	return (1);
}

int	parser_add_c(t_datas *data, char **line_spl)
{
	data->scene->cam.pos = read_vect(line_spl[1], data);
	data->scene->cam.dir = read_vect(line_spl[2], data);
	data->fov = (ft_atof(line_spl[3]) * PI) / 180;
	if (!is_good_dir(data->scene->cam.dir, data) || data->fov * 180 / PI > \
180.f || data->fov * 180 / PI < 0.f)
		print_error(data);
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
		print_error(data);
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
		print_error(data);
	res->is_damier = ft_atoi(line_spl[4]);
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
	res->color = read_vect(line_spl[5], data);
	if (!is_good_color(res->color, data) || \
!is_good_dir(((t_cylinder *)res->obj)->dir, data) || \
	((t_cylinder *)res->obj)->rayon < 0.f || \
	((t_cylinder *)res->obj)->hauteur < 0.f)
		print_error(data);
	data->scene->objs = add_tab_obj(data->scene->objs, res);
	return (1);
}