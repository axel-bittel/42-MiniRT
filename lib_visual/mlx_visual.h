/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_visual.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:23:36 by abittel           #+#    #+#             */
/*   Updated: 2021/12/01 23:09:27 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_VISUAL_H
# define MLX_VISUAL_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_per_pixel;
	int		line_length;
	int		endia;
	int		size_x;
	int		size_y;
}		t_img;
typedef struct s_subimg
{
	int	x;
	int	y;
	int	size_x;
	int	size_y;
}		t_subimg;
typedef struct s_tuple
{
	int	x;
	int	y;
}		t_tuple2D;

void	init_img(t_img *img, void *mlx, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);
void	print_col_in_img(t_img *dest, t_subimg data, int color);
void	print_line(t_img *dest, t_tuple2D t1, t_tuple2D t2);

#endif
