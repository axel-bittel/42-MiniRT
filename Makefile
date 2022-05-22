# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 15:56:11 by rahmed            #+#    #+#              #
#    Updated: 2022/05/17 15:56:11 by rahmed           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	MiniRT
NAMEB			=	MiniRT_bonus

ARG				=	${MAP_DIR}/map_tronche.rt
ARGB			=	${MAP_DIR}/map_tronche.rt

UNAME_S			:=	$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
OSFLAG			=	-DMACOS
MLX_DIR			=	${LIBVISUAL_DIR}/minilibx
MLXFLAGS		=	-L${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME_S),Linux)
OSFLAG			=	-DLINUX
MLX_DIR			=	${LIBVISUAL_DIR}/minilibx-linux
MLXFLAGS		=	-L${MLX_DIR} -lm -lmlx -lXext -lX11 -lz
endif

SRC_DIR			=	src
INC_DIR			=	include
LIBFT_DIR		=	libft
LIBFT_LIB		=	${LIBFT_DIR}/libft.a
LIBVISUAL_DIR	=	lib_visual
LIBVISUAL		=	${LIBVISUAL_DIR}/mlx_visual.c
MLX_LIB			=	${MLX_DIR}/libmlx.a
MAP_DIR			=	map

CC				=	gcc
RM				=	rm -f
AR				=	ar rcs
CFLAGS			=	-Wall -Wextra -Werror
FSFLAGS			=	-fsanitize=address
OFLAGS			=	-Ofast -fno-strict-aliasing \
					-fomit-frame-pointer -mtune=native -msse4.2 -mfpmath=sse \
					-march=native -funsafe-math-optimizations -funroll-loops \
					-ffast-math -flto -finline-functions \
					#${FSFLAGS}

SRCS			= 	${SRC_DIR}/main.c \
					${SRC_DIR}/cmd.c \
					${SRC_DIR}/cmd_change_obj.c \
					${SRC_DIR}/cmd_create_obj.c \
					${SRC_DIR}/cmd_get_prop.c \
					${SRC_DIR}/cmd_obj_tab_manip.c \
					${SRC_DIR}/cmd_print.c \
					${SRC_DIR}/inter_sect_sphere.c \
					${SRC_DIR}/vector3.c \
					${SRC_DIR}/cmd_utils.c \
					${SRC_DIR}/parser.c \
					${SRC_DIR}/intersec_cylinder.c \
					${SRC_DIR}/parser_add_obj.c \
					${SRC_DIR}/parser_utils.c \
					${SRC_DIR}/cmd_input.c \
					${SRC_DIR}/math_utils.c \
					${SRC_DIR}/vector3_bis.c \
					${SRC_DIR}/compute_screen.c \
					${SRC_DIR}/cmd_parse.c \
					${SRC_DIR}/cmd_parse_utils.c \
					${SRC_DIR}/parser_operation_utils.c \
					${SRC_DIR}/mlx_utils.c

BSRCS			=	${SRC_DIR}/main.c \
					${SRC_DIR}/cmd.c \
					${SRC_DIR}/cmd_change_obj.c \
					${SRC_DIR}/cmd_create_obj.c \
					${SRC_DIR}/cmd_get_prop.c \
					${SRC_DIR}/cmd_obj_tab_manip.c \
					${SRC_DIR}/cmd_print.c \
					${SRC_DIR}/inter_sect_sphere.c \
					${SRC_DIR}/vector3.c \
					${SRC_DIR}/cmd_utils.c \
					${SRC_DIR}/parser_bonus.c \
					${SRC_DIR}/intersec_cylinder.c \
					${SRC_DIR}/parser_add_obj_bonus.c \
					${SRC_DIR}/parser_utils.c \
					${SRC_DIR}/cmd_input.c \
					${SRC_DIR}/math_utils.c \
					${SRC_DIR}/vector3_bis.c \
					${SRC_DIR}/compute_screen_bonus.c \
					${SRC_DIR}/cmd_light_tab_manip_bonus.c \
					${SRC_DIR}/cmd_parse.c \
					${SRC_DIR}/cmd_parse_utils.c \
					${SRC_DIR}/parser_operation_utils.c \
					${SRC_DIR}/mlx_utils.c

INCLUDES		=	-I./${LIBFT_DIR} \
					-I./${INC_DIR} \
					-I./${LIBVISUAL_DIR} \
					-I./${MLX_DIR}

OSRCS			=	${SRCS:.c=.o}
OBSRCS			=	${BSRCS:.c=.o}
OLIBVISUAL		=	${LIBVISUAL:.c=.o}

LDFLAGS			=	-L. -L${LIBFT_DIR} -lft

%.o				:	%.c
					@echo "${TXT_BLUE}"
					@echo "~~~~~~~ MAKE PROJECT ~~~~~~~~"
					${CC} ${CFLAGS} ${INCLUDES} ${OSFLAG} -c $< -o ${<:.c=.o} -g
#${CC} ${CFLAGS} $(ARG) ${INCLUDES} -L${LIBVISUAL_DIR}/minilibx-linux -I${LIBVISUAL_DIR}/minilibx-linux -c $< -o ${<:.c=.o} -g
					@echo "${FANCY_RESET}"

${NAME}			:	$(OLIBVISUAL) ${OSRCS} ${LIBFT_LIB} ${MLX_LIB}
					@echo "${TXT_YELLOW}"
					@echo "~~~~~~~ COMPILATION ~~~~~~~~~"
					@echo "${TXT_GREEN}"
					${CC} ${OLIBVISUAL} ${OSRCS} ${CFLAGS} ${OFLAGS} ${LDFLAGS} ${MLXFLAGS} -o ${NAME} -g
#$(CC) $(OLIBVISUAL) ${OSRCS} ${INCLUDES} ${LDFLAGS} -L${LIBVISUAL_DIR}/minilibx-linux -lm -lmlx -lXext -lX11 -lz -o $(NAME) -g
					@echo "${FANCY_RESET}"

${MLX_LIB}		:
	$(MAKE) -C ./${MLX_DIR} re

${LIBFT_LIB} 	:
	$(MAKE) -C ${LIBFT_DIR}/ bonus

all			:	${NAME}

bonus		:	$(OLIBVISUAL) ${OBSRCS} ${LIBFT_LIB} ${MLX_LIB}
				${CC} $(OLIBVISUAL) ${OBSRCS} ${CFLAGS} ${OFLAGS} ${LDFLAGS} ${MLXFLAGS} -o $(NAMEB) -g
#$(CC) $(OLIBVISUAL) ${OBSRCS} ${INCLUDES} ${LDFLAGS} -L${LIBVISUAL_DIR}/minilibx-linux -lm -lmlx -lXext -lX11 -lm -lz -o $(NAME) -g

clean :
				@echo "${TXT_YELLOW}"
				@echo "~~~~~~~~~~ CLEAN ~~~~~~~~~~~~"
				@echo "${TXT_RED}"
				${RM}  ${OSRCS}
				${RM}  ${OBSRCS}
				${RM}  ${OLIBVISUAL}
				${RM}  ${MLX_LIB}
				$(MAKE) -C ${LIBFT_DIR}/ $@
				$(MAKE) -C ${MLX_DIR}/ $@
				@echo "$(FANCY_RESET)"

fclean		:	clean
				@echo "${TXT_YELLOW}"
				@echo "~~~~~~~~~~ FCLEAN ~~~~~~~~~~"
				@echo "${TXT_MAGENTA}"
				${RM} ${NAME} ${NAMEB} ${LIBFT_LIB}
				@echo "$(FANCY_RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re bonus
############### PARTIE TEST ###############
test		:
				make
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~   MiniRT   ~~~~~~~~~~~"
				@echo "${FANCY_RESET}"
				./${NAME} ${ARG}

testb		:
				make bonus
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~   MiniRT ~ BONUS  ~~~~~~~~"
				@echo "${FANCY_RESET}"
				./${NAMEB} ${ARGB}

norm		:
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~ CHECK LIB NORM ~~~~~~~~~"
				@echo "${TXT_GREEN}"
				norminette ${LIBFT_DIR}/*.c -R CheckForbiddenSourceHeader
				norminette ${LIBFT_DIR}/*.h -R CheckDefine
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~ CHECK PROJECT NORM ~~~~~~~"
				@echo "${TXT_CYAN}"
				norminette ${SRC_DIR}/*.c -R CheckForbiddenSourceHeader
				norminette ${LIBVISUAL_DIR}/*.c -R CheckForbiddenSourceHeader
				norminette ${INC_DIR}/*.h -R CheckDefine
				@echo "${FANCY_RESET}"

flush		:	fclean
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~ Extra-CLEANING  ~~~~~~~~"
				@echo "${TXT_RED}"
				${RM} ${NAME} ${NAMEB}
				${RM} .DS_STORE
				${RM} *.out
				${RM} *.a ${LIBFT_DIR}/*.a ${MLX_DIR}/*.a
				${RM} ${LIBVISUAL_DIR}/minilibx/*.o ${LIBVISUAL_DIR}/minilibx/*.a
				${RM} ${LIBVISUAL_DIR}/minilibx-linux/*.o ${LIBVISUAL_DIR}/minilibx-linux/*.a
				${RM} ${SRC_DIR}/*.o ${LIBFT_DIR}/*.o ${LIBVISUAL_DIR}/*.o
				${RM} -R *.dSYM
				@echo "${FANCY_RESET}"

# Set COLORS
TXT_RED		=	\033[1;31m
TXT_GREEN	=	\033[1;32m
TXT_YELLOW	=	\033[1;33m
TXT_BLUE	=	\033[1;34m
TXT_MAGENTA	=	\033[1;35m
TXT_CYAN	=	\033[1;36m
BCK_RED		=	\033[0;41m
BCK_GREEN	=	\033[0;42m
BCK_YELLOW	=	\033[0;43m
BCK_BLUE	=	\033[0;44m
BCK_MAGENTA	=	\033[0;45m
BCK_CYAN	=	\033[0;46m
FANCY_RESET	=	\033[0m
###########################################
