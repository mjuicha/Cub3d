


NAME = cub3D


SRCS =	bool_vars.c check_file.c check_map.c check_map2.c main.c event_hook.c free_game.c free_game2.c \
		ft_atoi.c get_colors.c get_next_line.c get_next_line_utils.c getters.c init_cub.c launch_game.c \
		load_textures.c map.c math_tools.c math_tools1.c mini_tools1.c player.c player_control.c start_game.c \
		texture_path.c tools.c cub_tools.c

OBJD = obj

OBJS = $(SRCS:%.c=$(OBJD)/%.o)


CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

$(OBJD)/%.o: %.c cub3d.h
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