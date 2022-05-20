/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:04:12 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 20:14:36 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# define ADD_CMD	1
# define LIST_CMD	2
# define CHANGE_CMD	3
# define DELETE_CMD	4
# define EXIT_CMD	5

float	ft_atof(char *s);
char	*mini_gnl(int fd);
void	free_tab_obj(t_obj **tab);
int		exec_cmd(t_datas *data);
int		get_vect(char *str, t_vect3 *res);
int		get_prop(char **str, t_vect3 *v, char *prop);
int		get_fprop(char **str, float *f, char *prop);
void	*create_new_cylinder(char **str);
void	*create_new_sphere(char **str);
void	*create_new_plane(char **str);
t_obj	**add_tab_obj(t_obj **tab, t_obj *new);
void	free_obj(t_obj *obj);
t_obj	**delete_tab_obj(t_obj **tab, int idx);
void	print_lights_prop(t_datas *data);
void	print_plane_prop(t_plane *cy);
void	print_sphere_prop(t_sphere *cy);
void	print_cylinder_prop(t_cylinder *cy);
void	print_vect(t_vect3 v, char *prop);
void	change_obj_light(t_datas *data, int idx, char **cmd);
void	change_obj_prop_cylinder(t_cylinder *sp, char **cmd);
void	change_obj_prop_plane(t_plane *sp, char **cmd);
void	change_obj_prop_sphere(t_sphere *sp, char **cmd);
t_vect3	read_vect(char *v, t_datas *data);
void	print_error(t_datas *data, size_t err);
int		is_cmd_exist(char *str);
int		exec_add_cmd(t_datas *datas, char **str);
int		exec_list_cmd(t_datas *data);
int		exec_change_cmd(t_datas *data, char **cmd);
float	deg_to_rad(float degrees);
float	rad_to_deg(float radians);

#endif
