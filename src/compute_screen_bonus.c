/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_screen_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:59:49 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 20:01:52 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_insity(t_datas *data, int k, t_res *res)
{
	int		i;
	t_vect3	color;

	color = data->scene->objs[k]->color;
	res->intensity.x = minf(color.x, data->scene->l_amb.color.x);
	res->intensity.y = minf(color.y, data->scene->l_amb.color.y);
	res->intensity.z = minf(color.z, data->scene->l_amb.color.z);
	res->intensity = mult_scal(res->intensity, data->scene->l_amb.intensity * \
data->scene->l_amb.ratio);
	i = -1;
	while (++i < data->scene->nb_light)
	{
		res->intensitys[i].x = minf(color.x, data->scene->l_tab[i]->color.x);
		res->intensitys[i].y = minf(color.y, data->scene->l_tab[i]->color.y);
		res->intensitys[i].z = minf(color.z, data->scene->l_tab[i]->color.z);
		res->intensitys[i] = mult_scal(res->intensitys[i], \
data->scene->l_tab[i]->intensity * data->scene->l_tab[i]->ratio * \
maxf(0.f, dot_product(res->normal, diff_vects(data->scene->\
l_tab[i]->pos, res->intersec))) / (4.f * M_PI * norm_square(\
diff_vects(data->scene->l_tab[i]->pos, res->intersec))));
		res->intensitys[i].x = powf(res->intensitys[i].x, 1.f / 2.22f);
		res->intensitys[i].y = powf(res->intensitys[i].y, 1.f / 2.22f);
		res->intensitys[i].z = powf(res->intensitys[i].z, 1.f / 2.22f);
	}
}

t_res	get_min_intersection(t_datas *data, t_ray inter)
{
	int		k;
	t_res	res;

	k = -1;
	res.norm = -1;
	res.intensitys = malloc(sizeof(t_vect3) * data->scene->nb_light);
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
	int		m;
	t_ray	inter_ray;

	inter_ray.pos = add_vects(res->lst_intersec, mult_scal(\
res->lst_norm, 0.000001));
	l = -1;
	while (data->scene->objs[++l])
	{
		m = -1;
		while (++m < data->scene->nb_light)
		{
			inter_ray.dir = norm_vect(diff_vects(data->scene->l_tab[m]->pos, \
inter_ray.pos));
			if (l != res->lst_k && is_intersection(inter_ray, \
*data->scene->objs[l], &res->intersec, &res->normal) && norm_square(diff_vects(\
inter_ray.pos, res->intersec)) - norm_square(diff_vects(data->scene->\
l_tab[m]->pos, inter_ray.pos)) < 0.1f)
			{
				res->intensitys[m] = mult_scal(res->intensitys[m], 0.f);
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
add_vect3(res.intensitys, 1, data->scene->nb_light))), minf(255.f, (\
res.intensity.y + add_vect3(res.intensitys, 2, data->scene->nb_light))), \
minf((res.intensity.z + add_vect3(res.intensitys, 3, data->scene->nb_light)), \
255.f), VECTOR3_SIZE));
	free(res.intensitys);
}

int	print_scene(t_datas *data)
{
	int		i;
	int		j;
	t_ray	inter;

	i = -1;
	if (data->scene->cam.dir.x + data->scene->cam.dir.y + \
data->scene->cam.dir.z == 0.f || data->fov == 0.f)
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
