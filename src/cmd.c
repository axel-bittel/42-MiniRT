/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:55 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 17:52:38 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	printf("exec_add_cmd - str[1] = %s\n", str[1]);//!test
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
	printf("exec_list_cmd\n");//!test
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
	printf("data->cmd  : %s / cmd_splt[1] = %s \n", data->cmd, cmd_splt[1]); // !test
	if (data->cmd && cmd_splt[1])
		inter = ft_atoi(cmd_splt[1]);
	if (!cmd_splt[0] || !is_cmd_exist(cmd_splt[0]))
		return (ft_free_tab(cmd_splt), print_cmd_error(ERR_CMD));
	if ((is_cmd_exist(cmd_splt[0]) == LIST_CMD) || \
	(is_cmd_exist(cmd_splt[0]) == EXIT_CMD) || \
	(is_cmd_exist(cmd_splt[0]) == ADD_CMD) || \
	(is_cmd_exist(cmd_splt[0]) == CHANGE_CMD))
		return (check_cmd(data, cmd_splt, is_cmd_exist(cmd_splt[0])));
	if (is_cmd_exist(cmd_splt[0]) == DELETE_CMD)
	{
		if (!cmd_splt[1] || !ft_isdigit(cmd_splt[1][0]))
			return (ft_free_tab(cmd_splt), print_cmd_error(ERR_CMD_NO_OBJ));
		if (inter < 3)
			return (ft_free_tab(cmd_splt), print_cmd_error(ERR_CMD_NO_DEL));
		data->scene->objs = delete_tab_obj(data->scene->objs, inter - 3);
	}
	return (ft_free_tab(cmd_splt), 2);
}

int	check_cmd(t_datas *data, char **cmd_splt, int type_cmd)
{
	if ((type_cmd == EXIT_CMD || type_cmd == LIST_CMD) && cmd_splt[1])
		return (ft_free_tab(cmd_splt), print_cmd_error(ERR_CMD_ARG), 0);
	else if (type_cmd == EXIT_CMD)
		return (ft_free_tab(cmd_splt), -1);
	else if (type_cmd == LIST_CMD)
		return (ft_free_tab(cmd_splt), exec_list_cmd(data), 0);
	if (type_cmd == ADD_CMD)
	{
		if (!check_cmd_add_args(cmd_splt))
			return (exec_add_cmd(data, cmd_splt), ft_free_tab(cmd_splt), 2);
		else
			return (ft_free_tab(cmd_splt), 0);
	}
	if (type_cmd == CHANGE_CMD) // && !check_cmd_change_args(cmd_splt)) // todo
		exec_change_cmd(data, cmd_splt);
	return (0);
}

int	check_cmd_add_args(char **cmd_splt)
{
	// ! case L to add in bonus
	if (((!cmd_splt[1]) || \
	(!ft_strncmp(cmd_splt[1], "sp", 3) && ft_tab_len(cmd_splt) > (3 + 2)) || \
	(!ft_strncmp(cmd_splt[1], "pl", 3) && ft_tab_len(cmd_splt) > (3 + 2)) || \
	(!ft_strncmp(cmd_splt[1], "cy", 3) && ft_tab_len(cmd_splt) > (5 + 2))) || \
	check_cmd_add_args_names(cmd_splt))
		return (print_cmd_error(ERR_CMD_ARG), 1);
	if (!ft_strncmp(cmd_splt[1], "sp", 3) || !ft_strncmp(cmd_splt[1], "pl", 3) \
	|| !ft_strncmp(cmd_splt[1], "cy", 3))
		return (0);
	return (print_cmd_error(ERR_CMD_NO_OBJ), 1);
}

int	check_cmd_add_args_names(char **cmd_splt)
{
	int		i;
	char	**names;
	int		check;
	int		old_check;

	i = 2;
	old_check = 0;
	if (!cmd_splt[1])
		return (1);
	if (!ft_strncmp(cmd_splt[1], "sp", 3))
		names = ft_split("pos= rayon= color=", ' ');
	else if (!ft_strncmp(cmd_splt[1], "pl", 3))
		names = ft_split("pos= dir= color=", ' ');
	else if (!ft_strncmp(cmd_splt[1], "cy", 3))
		names = ft_split("pos= dir= rayon= hauteur= color=", ' ');
	else
		return (1);
	while (cmd_splt[i])
	{
		check = is_valid_arg(cmd_splt[i], names);
		printf("cmd_splt[%d]-----check = %d - oldcheck = %d\n", i, check, old_check); //!test
		if (!check || (check & old_check))
			return (ft_free_tab(names), 1);
		old_check |= check;
		i++;
	}
	return (ft_free_tab(names), 0);
}

int	is_valid_arg(char *cmd_splt, char **names)
{
	int		j;
	int		check;

	j = 0;
	check = 0;
	while (names[j])
	{
		if (!ft_strncmp(cmd_splt, names[j], ft_strlen(names[j])))
			check |= 1 << j;
		j++;
	}
	printf("check valid arg = %d\n", check); //!test
	return (check);
}

int	check_cmd_change_args(char **cmd_splt) // todo
{
	(void)cmd_splt;
	return (print_cmd_error(ERR_CMD_NO_OBJ), 1);
}


int	print_cmd_error(size_t err)
{
	ft_putstr_fd("\033[1;31mError\n\033[0m", STDERR_FILENO);
	if (err == ERR_CMD)
		ft_putstr_fd("\033[1;31mCMD : Wrong command\n\033[0m", STDERR_FILENO);
	if (err == ERR_CMD_ARG)
		ft_putstr_fd("\033[1;31mCMD : Wrong argument\n\033[0m", STDERR_FILENO);
	if (err == ERR_CMD_NO_OBJ)
		ft_putstr_fd("\033[1;31mCMD : Wrong object selected\n\033[0m", \
		STDERR_FILENO);
	if (err == ERR_CMD_NO_DEL)
		ft_putstr_fd("\033[1;31mCMD : Can't delete this\n\033[0m", STDERR_FILENO);
	if (err == ERR_CMD_DUP_ARG)
		ft_putstr_fd("\033[1;31mCMD : Duplicate argument\n\033[0m", STDERR_FILENO);
	if (err == ERR_VECTOR)
		ft_putstr_fd("\033[1;31mCMD : Wrong vector\n\033[0m", STDERR_FILENO);
	return (0);
}
