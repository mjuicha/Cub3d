/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:15:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/29 03:06:05 by mjuicha          ###   ########.fr       */
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
	if (game->map[y][x] == 'D')
		game->is_door[ray] = 1;
	else
		game->is_door[ray] = 0;
}


t_door_pos *check_door(t_game *game, int mapx, int mapy)
{
    t_door_pos *door;
    door = malloc(sizeof(t_door_pos));
	if (!door)
		mlx_free(game, MALLOC_ERROR);

    door->x = 0;
    door->valid = 1;
    if (game->map[mapy - 1][mapx] == 'D' || game->map[mapy - 1][mapx] == 'd')
    {
        door->x = mapx;
        door->y = mapy - 1;
    }
    else if (game->map[mapy + 1][mapx] == 'D' || game->map[mapy + 1][mapx] == 'd')
    {
        door->x = mapx;
        door->y = mapy + 1;
    }
    else if (game->map[mapy][mapx - 1] == 'D' || game->map[mapy][mapx - 1] == 'd')
    {
        door->x = mapx - 1;
        door->y = mapy;
    }
    else if (game->map[mapy][mapx + 1] == 'D' || game->map[mapy][mapx + 1] == 'd')
    {
        door->x = mapx + 1;
        door->y = mapy;
    }
    else if (game->map[mapy - 1][mapx + 1] == 'D' || game->map[mapy - 1][mapx + 1] == 'd')
    {
        door->y = mapy - 1;
        door->x = mapx + 1;
    }
    else if (game->map[mapy - 1][mapx - 1] == 'D' || game->map[mapy - 1][mapx - 1] == 'd')
    {
        door->y = mapy - 1;
        door->x = mapx - 1;
    }
    else if (game->map[mapy + 1][mapx + 1] == 'D' || game->map[mapy + 1][mapx + 1] == 'd')
    {
        door->y = mapy + 1;
        door->x = mapx + 1;
    }
    else if (game->map[mapy + 1][mapx - 1] == 'D' || game->map[mapy + 1][mapx - 1] == 'd')
    {
        door->y = mapy + 1;
        door->x = mapx - 1;
    }
    else 
        door->valid = 0;
    return (door);
}

void	open_close_door(t_game *game)
{
	int	x;
	int	y;
	t_door_pos *door;

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
}
