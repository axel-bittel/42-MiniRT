/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:59:23 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 20:14:44 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# define TYPE_SPHERE 1
# define TYPE_PLANE 2
# define TYPE_CYLINDER 3

typedef struct s_ray
{
	t_vect3	pos;
	t_vect3	dir;
}				t_ray;

typedef struct s_sphere
{
	t_vect3	pos;
	float	rayon;
}				t_sphere;

typedef struct s_plane
{
	t_vect3	pos;
	t_vect3	v1;
	t_vect3	v2;
}				t_plane;

typedef struct s_cylinder
{
	t_vect3	pos;
	t_vect3	rot;
	t_vect3	dir;
	t_vect3	norm_one;
	t_vect3	norm_two;
	t_vect3	v_uni;
	float	rayon;
	float	hauteur;
}				t_cylinder;

typedef struct s_obj
{
	void	*obj;
	int		type;
	int		is_damier;
	t_vect3	color;
}				t_obj;

typedef struct s_light
{
	t_vect3	pos;
	t_vect3	color;
	float	intensity;
	float	ratio;
	int		is_ambiante;
}				t_light;

typedef struct s_scene
{
	int		nb_light;
	t_obj	**objs;
	t_ray	cam;
	t_vect3	cam_up;
	t_vect3	cam_right;
	t_light	l_amb;
	t_light	l;
	t_light	**l_tab;
}				t_scene;

typedef struct s_datas
{
	char	run;
	int		w_x;
	int		w_y;
	float	fov;
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_scene	*scene;
	int		put_cmd;
	char	*cmd;
}				t_datas;

typedef struct s_res
{
	float	norm;
	int		lst_k;
	t_vect3	lst_intersec;
	t_vect3	lst_norm;
	t_vect3	*intensitys;
	t_vect3	intensity;
	t_vect3	intensity_two;
	t_vect3	intersec;
	t_vect3	normal;
}				t_res;

int		is_intersection(t_ray dir, t_obj o, t_vect3 *inter, t_vect3 *norm);
int		is_intersection_cylinder(t_ray dir, t_cylinder c, \
t_vect3 *inter, t_vect3 *norm);
int		is_intersection_sphere(t_ray dir, t_sphere s, t_vect3 *inter, \
t_vect3 *norm);
int		is_intersection_plane(t_ray dir, t_plane p, t_vect3 *inter, \
t_vect3 *norm);
int		rgb_to_hex(int r, int g, int b, int a);
float	minf(float f1, float f2);
float	maxf(float f1, float f2);
int		lunch_cmd(t_datas *data);
t_datas	*init_mymlx(void);
int		refresh_screen(t_datas *data);
void	press_cmd(int keycode, t_datas *data, char *inter, t_subimg pos);
int		press_key(int keycode, t_datas *data);
int		close_win(t_datas *data);
void	print_min_intersec(t_datas *data, t_ray inter, int i, int j);
int		print_scene(t_datas *data);
t_light	**add_tab_light(t_light **tab, t_light *new);
void	free_tab_ligth(t_light **tab);

#endif
