/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:37:08 by abittel           #+#    #+#             */
/*   Updated: 2022/05/18 18:21:49 by rahmed           ###   ########.fr       */
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
	int		nb_args;
	int		ret;

	if (!ft_strncmp(line, "", 1) || !ft_strncmp(line, "\n", 2))
		return (0);
	line_splt = ft_split_charset(line, " \t");
	nb_args = count_line_split(line_splt);
	if (!nb_args)
		return (print_error(data, ERR_FILE_CONTENT), \
		ft_free_tab(line_splt), -1);
	ret = line_checker(line_splt, data, nb_args, 0);
	printf("%d\n", ret); // !Test
	if (ret != 0)
		return (ret);
	ft_free_tab(line_splt);
	return (0);
}
