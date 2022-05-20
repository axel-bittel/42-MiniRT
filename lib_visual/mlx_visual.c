/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 19:58:27 by abittel           #+#    #+#             */
/*   Updated: 2021/12/04 19:16:28 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img(t_img *img, void *mlx, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	img->img = mlx_new_image(mlx, x, y);
	img->addr = mlx_get_data_addr(img->img, &(img->b_per_pixel), \
&(img->line_length), &(img->endia));
	img->size_x = x;
	img->size_y = y;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img->size_x && y < img->size_y)
	{
		pixel = img->addr + (y * img->line_length + x * (img->b_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void	print_col_in_img(t_img *dest, t_subimg data, int color)
{
	int	x;
	int	y;

	x = data.x;
	y = data.y;
	while (y < dest->size_y && y < data.y + data.size_y)
	{
		while (x < dest->size_x && x < data.x + data.size_x)
		{
			put_pixel(dest, x, y, color);
			x++;
		}
		x = data.x;
		y++;
	}
}
