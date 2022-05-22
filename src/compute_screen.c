/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:59:49 by abittel           #+#    #+#             */
/*   Updated: 2022/05/22 11:37:21 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_insity(t_datas *data, int k, t_res *res)
{
	res->intensity.x = minf(data->scene->objs[k]->color.x, \
data->scene->l_amb.color.x);
	res->intensity.y = minf(data->scene->objs[k]->color.y, \
data->scene->l_amb.color.y);
	res->intensity.z = minf(data->scene->objs[k]->color.z, \
data->scene->l_amb.color.z);
	res->intensity = mult_scal(res->intensity, data->scene->l_amb.intensity * \
data->scene->l_amb.ratio);
	res->intensity_two = mult_scal(data->scene->objs[k]->color, \
data->scene->l.intensity * data->scene->l.ratio * maxf(0.f, dot_product(\
res->normal, diff_vects(data->scene->l.pos, res->intersec))) / (4.f * M_PI * \
norm_square(diff_vects(data->scene->l.pos, res->intersec))));
	res->intensity_two.x = powf(res->intensity_two.x, 1.f / 2.22f);
	res->intensity_two.y = powf(res->intensity_two.y, 1.f / 2.22f);
	res->intensity_two.z = powf(res->intensity_two.z, 1.f / 2.22f);
}

t_res	get_min_intersection(t_datas *data, t_ray inter)
{
	int		k;
	t_res	res;

	k = -1;
	res.norm = -1;
	while (data->scene->objs[++k])
	{
		if (is_intersection(inter, *data->scene->objs[k], \
		&res.intersec, &res.normal))
		{
			if (res.norm < 0 || norm_square(diff_vects(res.intersec, \
			inter.pos)) < res.norm)
			{
				res.norm = norm_square(diff_vects(res.intersec, inter.pos));
				res.lst_norm = res.normal;
				res.lst_intersec = res.intersec;
				res.lst_k = k;
				get_insity(data, k, &res);
			}
		}
	}
	return (res);
}

void	get_shadows(t_datas *data, t_res *res)
{
	int		l;
	t_ray	inter_ray;

	inter_ray.pos = res->lst_intersec;
	inter_ray.pos.x += 0.001 * res->lst_norm.x;
	inter_ray.pos.y += 0.001 * res->lst_norm.y;
	inter_ray.pos.z += 0.001 * res->lst_norm.z;
	inter_ray.dir = norm_vect(diff_vects(data->scene->l.pos, inter_ray.pos));
	l = -1;
	while (data->scene->objs[++l])
	{
		if (l != res->lst_k && \
is_intersection(inter_ray, *data->scene->objs[l], &res->intersec, &res->normal))
		{
			if (norm_square(diff_vects(inter_ray.pos, res->intersec)) - \
norm_square(diff_vects(data->scene->l.pos, inter_ray.pos)) < 0.001f)
			{
				res->intensity_two = mult_scal(res->intensity_two, 0.f);
				break ;
			}
		}
	}
}

void	print_min_intersec(t_datas *data, t_ray inter, int i, int j)
{
	t_res	res;

	res = get_min_intersection(data, inter);
	if (res.norm < 0)
	{
		put_pixel(&data->img, j, i, rgb_to_hex(0, 0, 0, 0));
		return ;
	}
	get_shadows(data, &res);
	put_pixel(&data->img, j, i, rgb_to_hex(minf(255., (res.intensity.x + \
res.intensity_two.x)), minf(255.f, (res.intensity.y + res.intensity_two.y)), \
minf((res.intensity.z + res.intensity_two.z), 255.f), 0));
}

int	print_scene(t_datas *data)
{
	int		i;
	int		j;
	t_ray	inter;

	i = -1;
	if (is_null(&data->scene->cam.dir) || data->fov == 0.f)
		return (0);
	inter.pos = data->scene->cam.pos;
	while (++i < data->w_y)
	{
		j = -1;
		while (++j < data->w_x)
		{
			inter.dir.x = (float)j - ((float)data->w_x / 2.f);
			inter.dir.y = (float)(data->w_y - i) - ((float)data->w_y / 2.f);
			inter.dir.z = data->w_x / (2.f * tanf(data->fov / 2.f));
			inter.dir = norm_vect(inter.dir);
			inter.dir = norm_vect(add_vects(add_vects(mult_scal(data->scene->\
cam_right, inter.dir.x), mult_scal(data->scene->cam_up, inter.dir.y)), \
mult_scal(data->scene->cam.dir, inter.dir.z)));
			print_min_intersec(data, inter, i, j);
		}
	}
	return (1);
}
