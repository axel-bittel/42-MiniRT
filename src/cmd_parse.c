/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:32 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/19 21:35:24 by rahmed           ###   ########.fr       */
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

	i = 1;
	old_check = 0;
	if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "sp", 3))
		names = ft_split("pos= rayon= color=", ' ');
	else if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "pl", 3))
		names = ft_split("pos= dir= color=", ' ');
	else if (cmd_splt[1] && !ft_strncmp(cmd_splt[1], "cy", 3))
		names = ft_split("pos= dir= rayon= hauteur= color=", ' ');
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

int	is_valid_arg(char *arg, char **names)
{
	int		j;
	int		check;

	j = 0;
	check = 0;
	while (names[j])
	{
		if (!ft_strncmp(arg, names[j], ft_strlen(names[j])))
		{
			if (!is_valid_arg_value(arg, names[j]))
				check |= (1 << j);
			else
				return (0);
		}
		j++;
	}
	return (check);
}

int	is_valid_arg_value(char *arg, char *name)
{
	int		i;
	char	**param;

	i = 0;
	param = ft_split_charset(arg, ",=");
	while (param[++i])
	{
		// printf("NAME %s / is_valid_arg_value PARAM = %s\n", name, param[i]);//!test
		if (((!ft_strncmp("dir=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < -1 || ft_atof(param[i]) > 1)) \
		|| ((!ft_strncmp("color=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < 0 || ft_atof(param[i]) > 255)) \
		|| (((!ft_strncmp("rayon=", name, ft_strlen(name))) || \
		(!ft_strncmp("hauteur=", name, ft_strlen(name)))) && \
		(ft_atof(param[i]) < 0)))
			return (ft_free_tab(param), print_cmd_error(ERR_OUT_OF_BOUNDS), 1);
	}
	return (ft_free_tab(param), 0);
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
	if (err == ERR_OUT_OF_BOUNDS)
		ft_putstr_fd("\033[1;31mCMD : Out of bounds\n\033[0m", STDERR_FILENO);
	return (0);
}
