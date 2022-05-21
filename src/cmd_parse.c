/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:32 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/21 15:34:52 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (type_cmd == CHANGE_CMD)
	{
		if (!check_cmd_change_args(data, cmd_splt))
			return (exec_change_cmd(data, cmd_splt), ft_free_tab(cmd_splt), 2);
		else
			return (ft_free_tab(cmd_splt), 0);
	}
	return (0);
}

int	check_cmd_change_args(t_datas *data, char **cmd_splt)
{
	int	idx;
	int	type;

	type = 0;
	idx = ft_atoi(cmd_splt[1]) - 3;
	if (cmd_splt[1] != NULL && idx >= -3)
	{
		if (idx >= 0)
			type = data->scene->objs[idx]->type;
		if ((cmd_splt[2] == NULL) || \
		(((idx == -3 || idx == -1) && ft_tab_len(cmd_splt) > (3 + 2)) || \
		(idx == -2 && ft_tab_len(cmd_splt) > (2 + 2)) || \
		(idx >= 0 && type == TYPE_CYLINDER && ft_tab_len(cmd_splt) > (5 + 2)) \
		|| (idx >= 0 && (type == TYPE_PLANE || type == TYPE_SPHERE) && \
		ft_tab_len(cmd_splt) > (3 + 2))) || \
		check_cmd_change_args_name(cmd_splt, type, idx))
			return (print_cmd_error(ERR_CMD_ARG), 1);
		if (ft_str_isdigit(cmd_splt[1]) && ft_atoi(cmd_splt[1]) >= 0 \
		&& cmd_splt[2])
			return (0);
	}
	return (print_cmd_error(ERR_CMD_NO_OBJ), 1);
}

int	check_cmd_change_args_name(char **cmd_splt, int type, int idx)
{
	int		i;
	int		check;
	int		old_check;
	char	**names;

	i = 1;
	old_check = 0;
	get_arg_change_names(&names, type, idx);
	if (idx < -3)
		return (1);
	while (cmd_splt[++i])
	{
		check = is_valid_arg(cmd_splt[i], names);
		if (!check)
			return (ft_free_tab(names), 1);
		if (check & old_check)
			return (ft_free_tab(names), print_cmd_error(ERR_CMD_DUP_ARG), 1);
		old_check |= check;
	}
	return (ft_free_tab(names), 0);
}

int	check_cmd_add_args(char **cmd_splt)
{
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

	i = 1;
	old_check = 0;
	if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "sp", 3))
		names = ft_split("pos= radius= color=", ' ');
	else if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "pl", 3))
		names = ft_split("pos= dir= color=", ' ');
	else if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "cy", 3))
		names = ft_split("pos= dir= radius= height= color=", ' ');
	else
		return (1);
	while (cmd_splt[++i])
	{
		check = is_valid_arg(cmd_splt[i], names);
		if (!check)
			return (ft_free_tab(names), 1);
		if (check & old_check)
			return (ft_free_tab(names), print_cmd_error(ERR_CMD_DUP_ARG), 1);
		old_check |= check;
	}
	return (ft_free_tab(names), 0);
}
