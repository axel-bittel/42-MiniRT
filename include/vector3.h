/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:48:47 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 11:03:18 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

typedef struct vect3
{
	float	x;
	float	y;
	float	z;
}			t_vect3;

t_vect3	mult_scal(t_vect3 v1, float scal);
t_vect3	add_vects(t_vect3 v1, t_vect3 v2);
t_vect3	diff_vects(t_vect3 v1, t_vect3 v2);
float	norm_square(t_vect3 v1);
t_vect3	norm_vect(t_vect3 v1);
t_vect3	prod_vect(t_vect3 v1, t_vect3 v2);
float	dot_product(t_vect3 v1, t_vect3 v2);
float	add_vect3(t_vect3 *v, int coord, int size);
int		is_null(t_vect3 *vect);

#endif
