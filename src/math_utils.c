/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:22:23 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 14:28:08 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_hex(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

float	minf(float f1, float f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

float	maxf(float f1, float f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

int	lunch_cmd(t_datas *data)
{
	int	inter;

	inter = exec_cmd(data);
	if (inter == 2)
		refresh_screen(data);
	else if (inter == -1)
	{
		if (data->scene && data->scene->objs)
			free_tab_obj(data->scene->objs);
		if (data->scene)
			free(data->scene);
		exit(0);
	}
	return (1);
}
