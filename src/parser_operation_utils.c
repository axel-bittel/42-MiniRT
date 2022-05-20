/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:03:32 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 20:07:06 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect3	read_vect(char *v, t_datas *data)
{
	t_vect3	res;
	int		i;
	int		pos;

	i = -1;
	pos = 1;
	res = (t_vect3){0.f, 0.f, 0.f};
	while (v[++i])
	{
		if ((ft_isdigit(v[i]) || v[i] == '-' || v[i] == '.') && pos <= 3)
		{
			res.x = ft_atof(v + i) * (pos == 1) + res.x * !(pos == 1);
			res.y = ft_atof(v + i) * (pos == 2) + res.y * !(pos == 2);
			res.z = ft_atof(v + i) * (pos == 3) + res.z * !(pos == 3);
			while (v[i] && v[i + 1] && (ft_isdigit(v[i]) || \
			v[i] == '-' || v[i] == '.'))
				i++;
			pos++;
		}
		else if (pos > 3)
			print_error(data, ERR_DATA);
	}
	if (pos != 4)
		print_error(data, ERR_DATA);
	return (res);
}

int	is_good_color(t_vect3 v, t_datas *data)
{
	if (v.x > 255.f || v.x < 0.f || v.y > 255.f || v.y < 0.f || v.z > 255.f || \
v.z < 0.f)
		print_error(data, ERR_DATA);
	return (1);
}

int	is_good_dir(t_vect3 v, t_datas *data)
{
	if (fabsf(v.x) > 1.f || fabsf(v.y) > 1.f || fabsf(v.z) > 1.f)
		print_error(data, ERR_DATA);
	return (1);
}

int	parser_add_a(t_datas *data, char **line_spl)
{
	data->scene->l_amb.ratio = ft_atof(line_spl[1]);
	data->scene->l_amb.color = read_vect(line_spl[2], data);
	if (data->scene->l_amb.ratio > 1.f || data->scene->l_amb.ratio < 0.f || \
!is_good_color(data->scene->l_amb.color, data))
		print_error(data, ERR_DATA);
	data->scene->l_amb.is_ambiante = 1;
	data->scene->l_amb.intensity = 1.0f;
	return (1);
}
