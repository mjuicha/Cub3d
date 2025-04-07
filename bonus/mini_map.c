/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:57:55 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/07 19:26:10 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures_map(t_game *game)
{
	game->mini_map = malloc(sizeof(t_mini_map));
	if (!game->mini_map)
		mlx_free(game, MALLOC_ERROR);
	game->mini_map->height = 16;
	game->mini_map->width = 16;
	game->is_map_text = 1;
	game->mini_map->player = texture_img(game, "textures/mini_map/red.xpm",
			&game->mini_map->height, &game->mini_map->width);
	game->mini_map->wall = texture_img(game, "textures/mini_map/black.xpm",
			&game->mini_map->height, &game->mini_map->width);
	game->mini_map->door = texture_img(game, "textures/mini_map/blue.xpm",
			&game->mini_map->height, &game->mini_map->width);
	game->mini_map->space = texture_img(game, "textures/mini_map/grey.xpm",
			&game->mini_map->height, &game->mini_map->width);
}

void	*map_color(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y > game->mapcounter
		|| x > (int)ft_strlen(game->map[y]))
		return (game->mini_map->space->img);
	if (!game->map[y][x])
		return (game->mini_map->space->img);
	if (game->map[y][x] == 'D' || game->map[y][x] == 'd')
		return (game->mini_map->door->img);
	if (game->map[y][x] == '1')
		return (game->mini_map->wall->img);
	return (game->mini_map->space->img);
}

void	map_2d(t_game *game, int mapx, int mapy)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	x = mapx - 5;
	y = mapy - 5;
	while (y <= mapy + 5)
	{
		j = 0;
		x = mapx - 5;
		while (x <= mapx + 5)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				map_color(game, x, y), j * 16, i * 16);
			x++;
			j++;
		}
		y++;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->mini_map->player->img, 5 * 16, 5 * 16);
}

void	mini_map(t_game *game)
{
	int	mapx;
	int	mapy;

	mapx = game->player->pos_x / game->height;
	mapy = game->player->pos_y / game->width;
	map_2d(game, mapx, mapy);
}
