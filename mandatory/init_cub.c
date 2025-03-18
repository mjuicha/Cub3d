/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:23:39 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 18:09:14 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	angle_dir(char c)
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

int	direction(char *line, t_game *game)
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
	if (direction(line + i, NULL))
		i += 2;
	while (line[i] == ' ')
		i++;
	return (i);
}

void	get_info(t_game *game)
{
	game->width = TILE_SIZE;
	game->height = TILE_SIZE;
	alloc_vars(game);
	game->texture_path = get_texture_path(game);
	game->player->walk_dir = 0;
	game->player->turn_dir = 0;
	game->player->side_dir = 0;
	game->player->move_speed = 4.0;
	game->player->rot_speed = 2.0 * (M_PI / 180);
	game->player->fov = 60 * (M_PI / 180);
	game->player->found_player = 0;
	game->off = 0;
}

t_game	*init_cub(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (!valid_input(ac, av))
		return (FAILURE);
	fd = valid_file(av);
	if (fd == -1)
		return (FAILURE);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		close(fd);
		return (NULL);
	}
	game->mapfd = fd;
	game->alloc_bool = malloc(sizeof(t_alloc));
	if (!game->alloc_bool)
	{
		close(fd);
		free(game);
		return (NULL);
	}
	init_bool(game);
	get_info(game);
	return (game);
}
