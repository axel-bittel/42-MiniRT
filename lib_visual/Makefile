# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abittel <abittel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 10:24:03 by abittel           #+#    #+#              #
#    Updated: 2021/12/04 15:00:24 by abittel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c mlx_visual.c
OSRCS	=	${SRCS:.c=.o}
HEADER	=	0
NAME	=	test

all : ${NAME}

%.o: %.c
	$(CC)  -Imlx -c $< -o $@

${NAME} :	${OSRCS}
	$(CC) ${OSRCS} -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	#$(CC) $(OLIBVISUAL) ${OSRCS} -Lminilibx-linux -lm -lmlx -lXext -lX11 -lm -lz -o $(NAME) -g
clean :
	rm -f ${OSRCS}
fclean : clean
	rm -f ${NAME}
re : fclean all
so:
	$(CC) -nostartfiles -fPIC dd$(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OSRCS)
.PHONY: all clean fclean re
