NAME = cub3d
# -Wall -Wextra -Werror
CFLAGS =  -lmlx -framework OpenGL -framework AppKit -g
CC = cc

SRC = cub3d.c \
	libft.c \
	libft/split.c \
	parsing/parsing.c \
	parsing/parse_options.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	drawing/drawing.c \
	ray_casting.c \
	calculations_fns.c \
	init/init.c

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

re : clean all