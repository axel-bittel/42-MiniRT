/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:28:29 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/20 20:24:46 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifdef MACOS
#  define VECTOR3_SIZE 0
#  include <mlx.h>
# endif
# ifdef LINUX
#  define VECTOR3_SIZE 255
#  include "minilibx-linux/mlx.h"
# endif

# include <fcntl.h>
# include <limits.h>
# include "mlx_visual.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "vector3.h"
# include "obj.h"
# include "cmd_input.h"
# include "cmd.h"
# include "cmd_parse.h"
# include "parser.h"

# define TRUE 1
# define FALSE 0

enum	e_errors
{
	ERR_ARGS = 1,
	ERR_FILENAME_FORMAT,
	ERR_OPEN_FILE,
	ERR_MALLOC,
	ERR_DATA,
	ERR_FILE_CONTENT,
	ERR_CMD,
	ERR_CMD_ARG,
	ERR_CMD_DUP_ARG,
	ERR_CMD_NO_OBJ,
	ERR_CMD_NO_DEL,
	ERR_VECTOR,
	ERR_OUT_OF_BOUNDS
};

#endif