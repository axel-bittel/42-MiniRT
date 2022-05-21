/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:08:35 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 14:27:56 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_datas	*init_mymlx(void)
{
	t_datas	*res;

	res = malloc (sizeof(t_datas));
	res->w_x = 1080;
	res->w_y = 720;
	res->mlx = mlx_init();
	res->mlx_win = mlx_new_window(res->mlx, res->w_x, res->w_y, "MiniRT");
	init_img(&res->img, res->mlx, res->w_x, res->w_y);
	res->scene = 0;
	res->put_cmd = 0;
	res->cmd = 0;
	res->run = 1;
	return (res);
}

int	refresh_screen(t_datas *data)
{
	ft_putstr_fd("Cumputing...\n", 1);
	print_scene(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	ft_putstr_fd("DISPLAY\n", 1);
	return (1);
}

void	press_cmd(int keycode, t_datas *data, char *inter, t_subimg pos)
{
	inter[0] = keycode;
	if (keycode == 65288 && ft_strlen(data->cmd))
		data->cmd = ft_substr(data->cmd, 0, ft_strlen(data->cmd) - 1);
	else if (keycode >= 32 && keycode <= 127 && !data->cmd)
		data->cmd = ft_strdup(inter);
	else if (keycode >= 32 && keycode <= 127)
		data->cmd = ft_strjoin3(data->cmd, inter);
	if (data->cmd)
	{
		print_col_in_img(&data->img, pos, \
0x00FFFFFF);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
		mlx_string_put(data->mlx, data->mlx_win, 10, 10, 0x00000000, data->cmd);
	}
	if (keycode == 65293)
	{
		data->put_cmd = 0;
		lunch_cmd(data);
		free(data->cmd);
		data->cmd = 0;
	}
}

int	press_key(int keycode, t_datas *data)
{
	t_subimg	pos;
	char		inter[2];

	inter[1] = 0;
	pos.size_x = data->w_x;
	pos.size_y = 40;
	pos.x = 0;
	pos.y = 0;
	if (!VECTOR3_SIZE)
		keycode = map_key(keycode);
	if (keycode == 'c' && data->put_cmd == 0)
	{
		data->put_cmd = 1;
		print_col_in_img(&data->img, pos, 0x00FFFFFF);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (data->put_cmd == 1)
		press_cmd(keycode, data, inter, pos);
	if (keycode == 65307)
		close_win(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int	close_win(t_datas *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->scene && data->scene->objs)
		free_tab_obj(data->scene->objs);
	if (data->scene)
		free(data->scene);
	exit(EXIT_SUCCESS);
}
