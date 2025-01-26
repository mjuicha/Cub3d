SRCS = cub3d.c get_next_line.c get_next_line_utils.c init_cub.c launch_game.c map.c start_game.c tools.c 
OBJD = obj
OBJS = $(SRCS:%.c=$(OBJD)/%.o)

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror 
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

$(OBJD)/%.o: %.c cub3d.h get_next_line.h
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJD)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re