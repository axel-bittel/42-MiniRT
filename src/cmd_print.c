/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:58:20 by abittel           #+#    #+#             */
/*   Updated: 2022/04/20 17:24:02 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	print_vect(t_vect3 v, char *prop)
{
	ft_putstr_fd(prop, 1);
	ft_putstr_fd("(", 1);
	ft_putfloat_fd(v.x, 1, 2);
	ft_putstr_fd(",", 1);
	ft_putfloat_fd(v.y, 1, 2);
	ft_putstr_fd(",", 1);
	ft_putfloat_fd(v.z, 1, 2);
	ft_putstr_fd(") ", 1);
}

void	print_cylinder_prop(t_cylinder *cy)
{
	ft_putstr_fd("cy ", 1);
	print_vect(cy->dir, "dir=");
	print_vect(cy->pos, "pos=");
	ft_putstr_fd("rayon=", 1);
	ft_putfloat_fd(cy->rayon, 1, 2);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd("hauteur=", 1);
	ft_putfloat_fd(cy->hauteur, 1, 2);
	ft_putstr_fd(" ", 1);
}

void	print_sphere_prop(t_sphere *cy)
{
	ft_putstr_fd("sp ", 1);
	print_vect(cy->pos, "pos=");
	ft_putstr_fd("rayon=", 1);
	ft_putfloat_fd(cy->rayon, 1, 2);
	ft_putstr_fd(" ", 1);
}

void	print_plane_prop(t_plane *cy)
{
	ft_putstr_fd("pl ", 1);
	print_vect(cy->pos, "pos=");
	print_vect(cy->v1, "dir=");
}

void	print_lights_prop(t_datas *data)
{
	ft_putstr_fd("0 C ", 1);
	print_vect(data->scene->cam.pos, "pos=");
	ft_putstr_fd(" ", 1);
	print_vect(data->scene->cam.dir, "dir=");
	ft_putstr_fd(" FOV=", 1);
	ft_putfloat_fd(data->fov, 1, 2);
	ft_putstr_fd("\n1 A ", 1);
	ft_putstr_fd("ratio=", 1);
	ft_putfloat_fd(data->scene->l_amb.ratio, 1, 2);
	ft_putstr_fd(" ", 1);
	print_vect(data->scene->l_amb.color, "color=");
	ft_putstr_fd("\n2 L ", 1);
	print_vect(data->scene->l.pos, "pos=");
	ft_putstr_fd(" ratio=", 1);
	ft_putfloat_fd(data->scene->l.ratio, 1, 2);
	ft_putstr_fd("\n", 1);
}
