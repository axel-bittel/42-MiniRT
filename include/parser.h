/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:20:08 by abittel           #+#    #+#             */
/*   Updated: 2022/05/18 18:34:06 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "obj.h"
# include <stdio.h>

# define TRUE 1
# define FALSE 0

enum	e_errors
{
	ERR_ARGS = 1,
	ERR_FILENAME_FORMAT,
	ERR_OPEN_FILE,
	ERR_MALLOC,
	ERR_DATA,
	ERR_FILE_CONTENT
};

int		read_line(char *line, t_datas *data);
int		parse_file(char *file, t_datas *data);
t_vect3	read_vect(char *v, t_datas *data);
int		is_good_color(t_vect3 v, t_datas *data);
int		is_good_dir(t_vect3 v, t_datas *data);
int		parser_add_a(t_datas *data, char **line_spl);
int		parser_add_l(t_datas *data, char **line_spl);
int		parser_add_c(t_datas *data, char **line_spl);
int		parser_add_sp(t_datas *data, char **line_spl);
int		parser_add_pl(t_datas *data, char **line_spl);
int		parser_add_cy(t_datas *data, char **line_spl);
int		check_file_ext(char *filename, t_datas *data);
int		count_line_split(char **line_splt);
int		line_checker(char **line_splt, t_datas *data, int args, int mandatory);

#endif
