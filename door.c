/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:15:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/01 18:50:06 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_door(t_game *game, int ray)
{
	int	x;
	int	y;

	x = game->wallx[ray];
	y = game->wally[ray];
	if (game->is_hor[ray])
		y = y + _up(game);
	else
		x = x + _left(game);
	x = x / game->width;
	y = y / game->height;
	if (game->map[y][x] && game->map[y][x] == 'D')
		game->is_door[ray] = 1;
	else
		game->is_door[ray] = 0;
}

int	is_door_surrounded(t_game *game, int x, int y)
{
	int	mapx;
	int	mapy;

	mapx = game->player->pos_x / game->width;
	mapy = game->player->pos_y / game->height;
	if (!(game->map[y][x] == 'D' || game->map[y][x] == 'd'))
		return (1);
	if ((game->map[y][mapx] == '1' || game->map[y][mapx] == 'D')
		&& (game->map[mapy][x] == '1' || game->map[mapy][x] == 'D'))
		return (1);
	return (0);
}

int	check_wall_door(t_game *game, int dir, int mapx, int mapy)
{
	int	x;
	int	y;

	x = mapx;
	y = mapy;
	if (dir == SOUTH_EAST || dir == SOUTH_WEST)
	{
		y++;
		if (dir == SOUTH_EAST)
			x++;
		else
			x--;
	}
	else if (dir == NORTH_EAST || dir == NORTH_WEST)
	{
		y--;
		if (dir == NORTH_EAST)
			x++;
		else
			x--;
	}
	if (is_door_surrounded(game, x, y))
		return (0);
	return (1);
}

t_door_pos	*check_door(t_game *game, int mapx, int mapy)
{
	t_door_pos	*door;
	int			dir;

	door = malloc(sizeof(t_door_pos));
	if (!door)
		mlx_free(game, MALLOC_ERROR);
	dir = cardinal_direction(game, mapx, mapy);
	if (dir == 0)
	{
		door->valid = 0;
		return (door);
	}
	door->x = door_dir_x(dir, mapx);
	door->y = door_dir_y(dir, mapy);
	if (game->map[door->y][door->x] == 'D'
		|| game->map[door->y][door->x] == 'd')
		door->valid = 1;
	else
		door->valid = 0;
	return (door);
}

void	open_close_door(t_game *game)
{
	t_door_pos	*door;
	int			x;
	int			y;

	x = game->player->pos_x / game->width;
	y = game->player->pos_y / game->height;
	door = check_door(game, x, y);
	if (door->valid)
	{
		if (game->map[door->y][door->x] == 'D')
			game->map[door->y][door->x] = 'd';
		else
			game->map[door->y][door->x] = 'D';
	}
	free(door);
}
