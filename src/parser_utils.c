/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:03:32 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 14:24:14 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(t_datas *data, size_t err)
{
	ft_putstr_fd("\033[1;31mError\n\033[0m", STDERR_FILENO);
	if (err == ERR_ARGS)
		ft_putstr_fd("\033[1;31mARGS : Format must be \
		./<MiniRT> <filename>.rt\n\033[0m", STDERR_FILENO);
	else if (err == ERR_FILENAME_FORMAT)
		ft_putstr_fd("\033[1;31mFILE : Format must be \
		<filename>.rt\n\033[0m", STDERR_FILENO);
	else if (err == ERR_OPEN_FILE)
		ft_putstr_fd("\033[1;31mFILE : Can't open\n\033[0m", STDERR_FILENO);
	else if (err == ERR_MALLOC)
		ft_putstr_fd("\033[1;31mMEMORY : Error on MALLOC\n\033[0m", STDERR_FILENO);
	else if (err == ERR_DATA)
		ft_putstr_fd("\033[1;31mDATA : Wrong values\n\033[0m", STDERR_FILENO);
	else if (err == ERR_FILE_CONTENT)
		ft_putstr_fd("\033[1;31mFILE : Content Problem\n\033[0m", STDERR_FILENO);
	if (data->scene && data->scene->objs)
		free_tab_obj(data->scene->objs);
	if (data->scene)
		free(data->scene);
	exit(EXIT_FAILURE);
}

int	count_line_split(char **line_splt)
{
	int		i;
	int		j;

	i = 1;
	while (line_splt[i])
	{
		j = 0;
		while (line_splt[i][j])
		{
			if (!ft_isdigit(line_splt[i][j]) && \
			line_splt[i][j] != '.' && line_splt[i][j] != ',' && \
			line_splt[i][j] != '+' && line_splt[i][j] != '-')
				return (0);
			j++;
		}
		i++;
	}
	return (i - 1);
}

int	line_checker(char **line_splt, t_datas *data, int args, int mandatory)
{
	if (!ft_strncmp(line_splt[0], "sp", 3) && args == 3)
		parser_add_sp(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "pl", 3) && args == 3)
		parser_add_pl(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "cy", 3) && args == 5)
		parser_add_cy(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "A", 2) && args == 2)
		return (parser_add_a(data, line_splt), ft_free_tab(line_splt), 1);
	else if (!ft_strncmp(line_splt[0], "L", 2) && \
	((mandatory && args == 2) || args == 3))
	{
		if (mandatory)
			return (parser_add_l(data, line_splt), ft_free_tab(line_splt), 2);
		return (parser_add_l(data, line_splt), 0);
	}
	else if (!ft_strncmp(line_splt[0], "C", 2) && args == 3)
		return (parser_add_c(data, line_splt), ft_free_tab(line_splt), 4);
	else
		return (print_error(data, ERR_FILE_CONTENT), \
		ft_free_tab(line_splt), -1);
	return (0);
}

int	check_file_ext(char *filename, t_datas *data)
{
	char	*ext;

	ext = ".rt";
	while ((*filename != '.') && *filename)
		++filename;
	while (*ext)
	{
		if (*filename == *ext)
		{
			++filename;
			++ext;
		}
		else
			print_error(data, ERR_FILENAME_FORMAT);
	}
	if (*filename)
		print_error(data, ERR_FILENAME_FORMAT);
	return (TRUE);
}

int	parse_file(char *file, t_datas *data)
{
	int		fd;
	char	*line;
	int		uniq;
	int		inter;

	uniq = 0;
	fd = open(file, O_RDONLY);
	data->scene = ft_calloc(sizeof(t_scene), 1);
	data->scene->l.intensity = 300000000.f / 255.f;
	data->scene->l_amb.intensity = 1;
	if (fd == -1)
		print_error(data, ERR_OPEN_FILE);
	line = mini_gnl(fd);
	while (line)
	{
		inter = read_line(line, data);
		if (uniq & inter)
			print_error(data, ERR_FILE_CONTENT);
		uniq = uniq | inter;
		free(line);
		line = mini_gnl(fd);
	}
	free(line);
	return (1);
}
