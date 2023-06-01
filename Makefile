NAME = cub3d
# -Wall -Wextra -Werror
CFLAGS =  -g -lmlx -framework OpenGL -framework AppKit -g -fsanitize=address
CC = cc

SRC = cub3d.c \
	libft/split.c \
	parsing/paarsing.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	drawing/drawing.c

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

re : clean all