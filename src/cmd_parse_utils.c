/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:30:32 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/21 15:34:52 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**get_arg_change_names(char ***names, int type, int idx)
{
	if (idx == -3)
		*names = ft_split("pos= dir= fov=", ' ');
	else if (idx == -2)
		*names = ft_split("ratio= color=", ' ');
	else if (idx == -1)
		*names = ft_split("pos= ratio= color=", ' ');
	else if (idx >= 0)
	{
		if (type == TYPE_CYLINDER)
			*names = ft_split("pos= dir= radius= height= color=", ' ');
		if (type == TYPE_PLANE)
			*names = ft_split("pos= dir= color=", ' ');
		if (type == TYPE_SPHERE)
			*names = ft_split("pos= radius= color=", ' ');
	}
	return (*names);
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
		if (((!ft_strncmp("dir=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < -1 || ft_atof(param[i]) > 1)) \
		|| ((!ft_strncmp("color=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < 0 || ft_atof(param[i]) > 255)) \
		|| ((!ft_strncmp("fov=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < 0 || ft_atof(param[i]) > 180)) \
		|| ((!ft_strncmp("ratio=", name, ft_strlen(name))) && \
		(ft_atof(param[i]) < 0 || ft_atof(param[i]) > 1)) \
		|| (((!ft_strncmp("radius=", name, ft_strlen(name))) || \
		(!ft_strncmp("height=", name, ft_strlen(name)))) && \
		(ft_atof(param[i]) < 0)))
			return (ft_free_tab(param), print_cmd_error(ERR_OUT_OF_BOUNDS), 1);
		if (!ft_str_isdigit(param[i]))
			return (ft_free_tab(param), 1);
	}
	return (ft_free_tab(param), 0);
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
