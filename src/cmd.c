/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:55 by abittel           #+#    #+#             */
/*   Updated: 2022/04/20 19:24:22 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	is_cmd_exist(char *str)
{
	if (!ft_strncmp(str, "add", 4))
		return (ADD_CMD);
	if (!ft_strncmp(str, "list", 6))
		return (LIST_CMD);
	if (!ft_strncmp(str, "change", 7))
		return (CHANGE_CMD);
	if (!ft_strncmp(str, "delete", 7))
		return (DELETE_CMD);
	if (!ft_strncmp(str, "exit", 6))
		return (EXIT_CMD);
	return (0);
}

int	exec_add_cmd(t_datas *datas, char **str)
{
	t_obj	*new_obj;

	new_obj = malloc(sizeof(t_obj));
	if (!ft_strncmp(str[1], "sp", 3))
	{
		new_obj->obj = create_new_sphere(str);
		new_obj->type = TYPE_SPHERE;
	}
	if (!ft_strncmp(str[1], "pl", 3))
	{
		new_obj->obj = create_new_plane(str);
		new_obj->type = TYPE_PLANE;
	}
	if (!ft_strncmp(str[1], "cy", 3))
	{
		new_obj->obj = create_new_cylinder(str);
		new_obj->type = TYPE_CYLINDER;
	}
	get_prop(str, &new_obj->color, "color=");
	datas->scene->objs = add_tab_obj(datas->scene->objs, new_obj);
	return (1);
}

int	exec_list_cmd(t_datas *data)
{
	int	i;

	i = -1;
	print_lights_prop(data);
	while (data->scene->objs[++i])
	{
		ft_putnbr_fd(i + 3, 1);
		ft_putstr_fd(" ", 1);
		if (data->scene->objs[i]->type == TYPE_SPHERE)
			print_sphere_prop((t_sphere *)data->scene->objs[i]->obj);
		if (data->scene->objs[i]->type == TYPE_CYLINDER)
			print_cylinder_prop((t_cylinder *)data->scene->objs[i]->obj);
		if (data->scene->objs[i]->type == TYPE_PLANE)
			print_plane_prop((t_plane *)data->scene->objs[i]->obj);
		print_vect(data->scene->objs[i]->color, "color=");
		ft_putstr_fd("\n", 1);
	}
	return (1);
}

int	exec_change_cmd(t_datas *data, char **cmd)
{
	int		idx;
	t_vect3	inter;

	idx = ft_atoi(cmd[1]);
	idx -= 3;
	if (idx >= -3 && idx < 0)
	{
		change_obj_light(data, idx, cmd);
		return (1);
	}
	if (data->scene->objs[idx]->type == TYPE_SPHERE)
		change_obj_prop_sphere((t_sphere *)data->scene->objs[idx]->obj, cmd);
	if (data->scene->objs[idx]->type == TYPE_PLANE)
		change_obj_prop_plane((t_plane *)data->scene->objs[idx]->obj, cmd);
	if (data->scene->objs[idx]->type == TYPE_CYLINDER)
		change_obj_prop_cylinder((t_cylinder *)data->scene->objs[idx]->obj, \
cmd);
	if (get_prop(cmd, &inter, "color="))
		data->scene->objs[idx]->color = inter;
	return (1);
}

int	exec_cmd(t_datas *data)
{
	char	**cmd_splt;
	int		inter;

	cmd_splt = ft_split(data->cmd, ' ');
	if (data->cmd && cmd_splt[1])
		inter = ft_atoi(cmd_splt[1]);
	if (!cmd_splt[0] || !is_cmd_exist(cmd_splt[0]))
		return (free(cmd_splt), ft_putstr_fd("error\n", 1), 0);
	if (is_cmd_exist(cmd_splt[0]) == EXIT_CMD)
		return (free(cmd_splt), -1);
	if (is_cmd_exist(cmd_splt[0]) == ADD_CMD && cmd_splt[1])
		exec_add_cmd(data, cmd_splt);
	if (is_cmd_exist(cmd_splt[0]) == LIST_CMD)
		return (exec_list_cmd(data), 0);
	if (is_cmd_exist(cmd_splt[0]) == DELETE_CMD)
	{
		if (!cmd_splt[1] || !ft_isdigit(cmd_splt[1][0]))
			return (ft_putstr_fd("NO OBJ SELECTED\n", 1), 0);
		if (inter < 3)
			return (ft_putstr_fd("CAN'T DELETE THIS\n", 1), 0);
		data->scene->objs = delete_tab_obj(data->scene->objs, inter - 3);
	}
	if (is_cmd_exist(cmd_splt[0]) == CHANGE_CMD && cmd_splt[1])
		exec_change_cmd(data, cmd_splt);
	return (free(cmd_splt), 2);
}