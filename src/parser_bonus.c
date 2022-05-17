/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:37:08 by abittel           #+#    #+#             */
/*   Updated: 2022/05/17 23:37:43 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "obj.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "parser.h"

int	read_line(char *line, t_datas *data)
{
	char	**line_splt;

	if (!ft_strncmp(line, "", 1) || !ft_strncmp(line, "\n", 2))
		return (0);
	line_splt = ft_split(line, ' ');
	if (!ft_strncmp(line_splt[0], "sp", 2))
		parser_add_sp(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "pl", 2))
		parser_add_pl(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "cy", 2))
		parser_add_cy(data, line_splt);
	else if (!ft_strncmp(line_splt[0], "A", 2))
		return (parser_add_a(data, line_splt), 1);
	else if (!ft_strncmp(line_splt[0], "L", 2))
		return (parser_add_l(data, line_splt), 0);
	else if (!ft_strncmp(line_splt[0], "C", 2))
		return (parser_add_c(data, line_splt), 4);
	else
		return (print_error(data, ERR_FILE_CONTENT), -1);
	return (0);
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
	return (1);
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
