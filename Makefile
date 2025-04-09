NAME 	= 		cub3D

BONUS	= 		cub3D_bonus

SRCS 	= 	 	mandatory/bool_vars.c \
				mandatory/check_file.c \
				mandatory/check_map.c \
				mandatory/check_map2.c \
				mandatory/cub3d.c \
				mandatory/event_hook.c \
				mandatory/free_game.c \
				mandatory/free_game2.c \
				mandatory/ft_atoi.c \
				mandatory/get_colors.c \
				mandatory/get_next_line.c \
				mandatory/get_next_line_utils.c \
				mandatory/getters.c \
				mandatory/init_cub.c \
				mandatory/launch_game.c \
				mandatory/load_textures.c \
				mandatory/map.c \
				mandatory/math_tools.c \
				mandatory/math_tools1.c \
				mandatory/mini_tools1.c \
				mandatory/player.c \
				mandatory/player_control.c \
				mandatory/start_game.c \
				mandatory/texture_path.c \
				mandatory/tools.c \
				mandatory/cub_tools.c \
				mandatory/init_data.c


OBJS = 			$(SRCS:%.c=%.o)


SRCS_BONUS = 	bonus/bool_vars_bonus.c \
				bonus/check_file_bonus.c \
				bonus/check_map_bonus.c \
				bonus/check_map2_bonus.c \
				bonus/cub3d_bonus.c \
				bonus/event_hook_bonus.c \
				bonus/free_game_bonus.c \
				bonus/free_game2_bonus.c \
				bonus/ft_atoi_bonus.c \
				bonus/get_colors_bonus.c \
				bonus/get_next_line_bonus.c \
				bonus/get_next_line_utils_bonus.c \
				bonus/getters_bonus.c \
				bonus/init_cub_bonus.c \
				bonus/launch_game_bonus.c \
				bonus/load_textures_bonus.c \
				bonus/map_bonus.c \
				bonus/math_tools_bonus.c \
				bonus/math_tools1_bonus.c \
				bonus/mini_tools1_bonus.c \
				bonus/player_bonus.c \
				bonus/player_control_bonus.c \
				bonus/start_game_bonus.c \
				bonus/texture_path_bonus.c \
				bonus/tools_bonus.c \
				bonus/cub_tools_bonus.c \
				bonus/init_data_bonus.c \
				bonus/door_bonus.c \
				bonus/dir_door_bonus.c \
				bonus/mini_map_bonus.c \
				bonus/animated_sprite_bonus.c \
				bonus/mouse_move_bonus.c


OBJS_BONUS 	= 	$(SRCS_BONUS:%.c=%.o)

CC 			= 	cc

CFLAGS 		=	-Wall -Wextra -Werror

MLXFLAGS 	= 	-lmlx -framework OpenGL -framework AppKit

all : 	$(NAME)
	

bonus : $(BONUS)



$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS)


$(BONUS) : $(OBJS_BONUS)
			$(CC) $(CFLAGS) $(MLXFLAGS) -o $(BONUS) $(OBJS_BONUS)


%.o: %.c cub3d.h
			$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %_bonus.c cub3d_bonus.h
			$(CC) $(CFLAGS) -c $< -o $@



clean :
		rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
		rm -rf $(NAME) $(BONUS)

re:		 fclean all

.PHONY:	 all clean fclean re