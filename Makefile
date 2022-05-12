# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abittel <abittel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 10:24:03 by abittel           #+#    #+#              #
#    Updated: 2022/05/12 18:02:21 by abittel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS	= 	src/main.c \
			src/cmd.c \
			src/cmd_change_obj.c \
			src/cmd_create_obj.c \
			src/cmd_get_prop.c \
			src/cmd_obj_tab_manip.c \
			src/cmd_print.c \
			src/inter_sect_sphere.c \
			src/vector3.c \
			src/cmd_utils.c \
			src/parser.c \
			src/intersec_cylinder.c \
			src/parser_add_obj.c \
			src/parser_utils.c \
			src/cmd_input.c \
			src/math_utils.c \
			src/vector3_bis.c \
			src/compute_screen.c
BSRCS	= 	src/main.c \
			src/cmd.c \
			src/cmd_change_obj.c \
			src/cmd_create_obj.c \
			src/cmd_get_prop.c \
			src/cmd_obj_tab_manip.c \
			src/cmd_print.c \
			src/inter_sect_sphere.c \
			src/vector3.c \
			src/cmd_utils.c \
			src/parser_bonus.c \
			src/intersec_cylinder.c \
			src/parser_add_obj_bonus.c \
			src/parser_utils.c \
			src/cmd_input.c \
			src/math_utils.c \
			src/vector3_bis.c \
			src/compute_screen_bonus.c \
			src/cmd_light_tab_manip_bonus.c
INCLUDES =  -I./libft \
			-I./include \
			-I./lib_visual
LIBVISUAL = lib_visual/mlx_visual.c
OLIBVISUAL = ${LIBVISUAL:.c=.o}
OSRCS	=	${SRCS:.c=.o}
OBSRCS	=	${BSRCS:.c=.o}
NAME	=	MiniRT
ARG = 	-Ofast -fsanitize=address -fno-strict-aliasing \
		-fomit-frame-pointer -mtune=native -msse4.2 -mfpmath=sse \
		-march=native -funsafe-math-optimizations -funroll-loops \
		-ffast-math -flto -finline-functions

all : ${NAME}

%.o: %.c
	#gcc -Wall -Wextra -Werror ${INCLUDES} -Ilib_visual/minilibx -c $< -o ${<:.c=.o} -g
	gcc -Wall -Wextra -Werror $(ARG) ${INCLUDES} -Llib_visual/minilibx-linux -Ilib_visual/minilibx-linux -Llibft -lft -c $< -o ${<:.c=.o} -g
bonus : $(OLIBVISUAL) ${OBSRCS} libft/libft.a 
	#gcc -Wall -Werror -Wextra -Llibft -lft -Llib_visual/minilibx -lmlx $(OLIBVISUAL) -framework OpenGL -framework AppKit ${OBSRCS} -o $(NAME) -g
	$(CC) $(OLIBVISUAL) ${OBSRCS} ${INCLUDES} -Llibft -lft -Llib_visual/minilibx-linux -lm -lmlx -lXext -lX11 -lm -lz -o $(NAME) -g
${NAME} :	$(OLIBVISUAL) ${OSRCS} libft/libft.a 
	#gcc -Wall -Werror -Wextra -Llibft -lft -Llib_visual/minilibx -lmlx $(OLIBVISUAL) -framework OpenGL -framework AppKit ${OSRCS} -o $(NAME) -g
	$(CC) $(OLIBVISUAL) ${OSRCS} ${INCLUDES} -Llibft -lft -Llib_visual/minilibx-linux -lm -lmlx -lXext -lX11 -lm -lz -o $(NAME) -g
lib_visual/minilibx/libmlx.a:
	$(MAKE) -C ./lib_visual/minilibx re
libft/libft.a :
	$(MAKE) -C libft/ bonus
clean :
	rm -f ${OSRCS}
	rm -f ${OBSRCS}
	rm -f ${OLIBVISUAL}
	rm -f lib_visual/minilibx/libmlx.a
	$(MAKE) -C libft/ $@
fclean : clean
	rm -f ${NAME}
	$(MAKE) -C libft/ $@
re : fclean all
.PHONY: all clean fclean re
