/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:23:39 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 12:23:43 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_angle_dir(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'E')
		return (0);
	return (0);
}

int	wall_txt_direction(char *line, t_game_data *game)
{
	if (ft_strchr2(line, "NO"))
		return (1);
	if (ft_strchr2(line, "SO"))
		return (2);
	if (ft_strchr2(line, "WE"))
		return (3);
	if (ft_strchr2(line, "EA"))
		return (4);
	if (ft_strchr2(line, "F "))
		get_color(line, game, 'F');
	if (ft_strchr2(line, "C "))
		get_color(line, game, 'C');
	return (0);
}

int	skip(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (wall_txt_direction(line + i, NULL))
		i += 2;
	while (line[i] == ' ')
		i++;
	return (i);
}

void	get_info(t_game_data *game)
{
	game->width = TILE_SIZE;
	game->height = TILE_SIZE;
	alloc_vars(game);
	game->texture_path = get_texture_path(game);
	game->player->walk_dir = 0;
	game->player->turn_dir = 0;
	game->player->side_dir = 0;
	game->player->move_speed = 5.0;
	game->player->rot_speed = 2.5 * (M_PI / 180);
	game->player->fov = 60 * (M_PI / 180);
	game->player->found_player = 0;
	game->off = 0;
}

t_game_data	*init_cub(int ac, char **av)
{
	t_game_data	*game;
	int			fd;

	if (!valid_input(ac, av))
		return (FAILURE);
	game = malloc(sizeof(t_game_data));
	if (!game)
		return (NULL);
	fd = valid_file(av);
	if (fd == -1)
		return (FAILURE);
	game->mapfd = fd;
	game->alloc_bool = malloc(sizeof(t_alloc));
	if (!game->alloc_bool)
		return (close(fd), free(game), NULL);
	init_bool(game);
	get_info(game);
	return (game);
}
