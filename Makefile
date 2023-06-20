NAME = cub3d
# -Wall -Wextra -Werror
CFLAGS =  -lmlx -framework OpenGL -framework AppKit
CC = cc

SRC =   drawing/drawing.c \
		drawing/rendering_walls.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line.h \
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

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC)

clean :
	rm -rf $(NAME)

re : clean all