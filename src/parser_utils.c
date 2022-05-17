/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:03:32 by abittel           #+#    #+#             */
/*   Updated: 2022/05/17 21:27:50 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "obj.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "parser.h"

// void	print_error(t_datas *data)
// {
// 	ft_putstr_fd("Error\n", 1);
// 	free_tab_obj(data->scene->objs);
// 	free(data->scene);
// 	exit (0);
// }

void	print_error(t_datas *data, size_t err)
{
	ft_putstr_fd("\033[1;31mError\n\033[0m", STDERR_FILENO);
	if (err == ERR_ARGS)
		ft_putstr_fd("\033[1;31mARGS : Format must be \
		./<MiniRT> <filename>.rt\n\033[0m", STDERR_FILENO);
	else if (err == ERR_FILENAME_FORMAT)
		ft_putstr_fd("\033[1;31mFILE : Format must be \
		<filename>.rt\n\033[0m", STDERR_FILENO);
	else if (err == ERR_OPEN_FILE)
		ft_putstr_fd("\033[1;31mFILE : Can't open\n\033[0m", STDERR_FILENO);
	else if (err == ERR_MALLOC)
		ft_putstr_fd("\033[1;31mMEMORY : Error on MALLOC\n\033[0m", STDERR_FILENO);
	else if (err == ERR_DATA)
		ft_putstr_fd("\033[1;31mDATA : Wrong values\n\033[0m", STDERR_FILENO);
	else if (err == ERR_FILE_CONTENT)
		ft_putstr_fd("\033[1;31mFILE : Content Problem\n\033[0m", STDERR_FILENO);
	if (data->scene && data->scene->objs)
		free_tab_obj(data->scene->objs);
	if (data->scene)
		free(data->scene);
	exit(EXIT_FAILURE);
}

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
			while (v[i] && v[i + 1] && (ft_isdigit(v[i]) || v[i] \
	== '-' || v[i] == '.'))
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
