/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:58:20 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 16:48:26 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vect(t_vect3 v, char *prop)
{
	printf("\033[1;36m\t*%s\033[1;33m(%5.2f, %5.2f, %5.2f)\033[0m", \
	prop, v.x, v.y, v.z);
}

void	print_cylinder_prop(t_cylinder *cy)
{
	printf("\033[1;36m>\033[1;32mcy\033[0m");
	print_vect(cy->pos, "pos=");
	print_vect(cy->dir, "dir=");
	printf("\033[1;36m\t*radius= \033[1;33m%.2f\
\033[1;36m\t*height= \033[1;33m%.2f\033[0m", cy->rayon, cy->hauteur);
}

void	print_sphere_prop(t_sphere *cy)
{
	printf("\033[1;36m>\033[1;32msp\033[0m");
	print_vect(cy->pos, "pos=");
	printf("\033[1;36m\t*radius= \033[1;33m%.2f\t\t\033[0m", cy->rayon);
}

void	print_plane_prop(t_plane *cy)
{
	printf("\033[1;36m>\033[1;32mpl\033[0m");
	print_vect(cy->pos, "pos=");
	print_vect(cy->v1, "dir=");
}

void	print_lights_prop(t_datas *data)
{
	printf("\033[1;34m>>LIST :\n\033[0m0 \033[1;36m>\033[1;32mC\033[0m");
	print_vect(data->scene->cam.pos, "pos=");
	print_vect(data->scene->cam.dir, "dir=");
	printf("\033[1;36m\t*FOV=\033[1;33m%.2f\033[0m", rad_to_deg(data->fov));
	printf("\n1 \033[1;36m>\033[1;32mA\033[1;36m\t*ratio= \033[1;33m%.2f\t\t", \
	data->scene->l_amb.ratio);
	print_vect(data->scene->l_amb.color, "color=");
	printf("\n2 \033[1;36m>\033[1;32mL\033[0m");
	print_vect(data->scene->l.pos, "pos=");
	printf("\033[1;36m\t*ratio= \033[1;33m%.2f\033[0m\n", data->scene->l.ratio);
}
