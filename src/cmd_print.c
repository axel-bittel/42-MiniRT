/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:58:20 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 15:26:06 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vect(t_vect3 v, char *prop)
{
	printf("\033[1;36m\t|\033[0m");
	printf("%s", prop);
	printf("(");
	printf("%.2f", v.x);
	printf(",");
	printf("%.2f", v.y);
	printf(",");
	printf("%.2f", v.z);
	printf(") ");
}

void	print_cylinder_prop(t_cylinder *cy)
{
	printf("\033[1;36m\t|\033[0m");
	printf("\033[1;32mcy\033[0m");
	print_vect(cy->pos, "pos=");
	print_vect(cy->dir, "dir=");
	printf("\033[1;36m\t|\033[0m");
	printf("rayon=");
	printf("%.2f", cy->rayon);
	printf("\033[1;36m\t|\033[0m");
	printf("hauteur=");
	printf("%.2f", cy->hauteur);
}

void	print_sphere_prop(t_sphere *cy)
{
	printf("\033[1;36m\t|\033[0m");
	printf("\033[1;32msp\033[0m");
	print_vect(cy->pos, "pos=");
	printf("\033[1;36m\t|\033[0m");
	printf("rayon=");
	printf("%.2f", cy->rayon);
	printf("\t");
}

void	print_plane_prop(t_plane *cy)
{
	printf("\033[1;36m\t|\033[0m");
	printf("\033[1;32mpl\033[0m");
	print_vect(cy->pos, "pos=");
	print_vect(cy->v1, "dir=");
}

void	print_lights_prop(t_datas *data)
{
	printf("\033[1;34m>>LIST :\n\033[0m");
	printf("0\033[1;36m\t|\033[1;32mC\033[0m");
	print_vect(data->scene->cam.pos, "pos=");
	printf("\t");
	print_vect(data->scene->cam.dir, "dir=");
	printf("\033[1;36m\t|\033[0m");
	printf("FOV=");
	printf("%.2f",rad_to_deg(data->fov));
	printf("\n1\033[1;36m\t|\033[1;32mA\033[0m");
	printf("\033[1;36m\t|\033[0m");
	printf("ratio=");
	printf("%.2f",data->scene->l_amb.ratio);
	printf("\t");
	print_vect(data->scene->l_amb.color, "color=");
	printf("\n2\033[1;36m\t|\033[1;32mL\033[0m");
	print_vect(data->scene->l.pos, "pos=");
	printf("\033[1;36m\t|\033[0m");
	printf("ratio=");
	printf("%.2f",data->scene->l.ratio);
	printf("\n");
}
