NAME = cub3D
LINK =  -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
CC = cc
HEADER = cub3d.h get_next_line/get_next_line.h

SRCS =	drawing/drawing.c \
		drawing/rendering_walls.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		init/init.c \
		libft/split.c \
		libft/utils.c \
		libft/utils2.c \
		parsing/analyse_map.c \
		parsing/parse_options.c \
		parsing/parse_options2.c \
		parsing/parsing.c \
		calculations_fns.c \
		cub3d.c \
		keys_handler.c \
		ray_casting.c \
		ray_casting2.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	$(CC) $(CFLAGS) $(LINK) $(OBJS) -o $(NAME)

%.o : %.c ${HEADER}
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all