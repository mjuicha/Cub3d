/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:15:23 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/31 04:06:22 by mjuicha          ###   ########.fr       */
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

int check_wall_door(t_game *game, int dir, int mapx, int mapy)
{
    int x;
    int y;

    x = mapx;
    y = mapy;
    if (dir == SOUTH_EAST)
    {
        x++;
        y++;
    }
    else if (dir == SOUTH_WEST)
    {
        x--;
        y++;
    }
    else if (dir == NORTH_EAST)
    {
        x++;
        y--;
    }
    else if (dir == NORTH_WEST)
    {
        x--;
        y--;
    }
    printf("invalid on %d %d\n", mapx, mapy);
    printf("invalid on %d %d\n", x, y);
    printf("door %c\n", game->map[y][mapx]);
    printf("player %c\n", game->map[mapy][x]);
    if (!(game->map[y][x] == 'D' || game->map[y][x] == 'd'))
        return (0);
    if ((game->map[y][mapx] == '1' || game->map[y][mapx] == 'D') && (game->map[mapy][x] == '1' || game->map[mapy][x] == 'D'))
        return (printf("deux murs\n"), 0);
    return (printf("dsdsdasdasdasDaseux murs\n"),1);
}


int    cardinal_direction(t_game *game, int mapx, int mapy)
{
    double  angle;
    int     ret;

    angle = game->player->angle;
    angle = normalize_angle(angle);
    ret = 0;
    if (angle <= M_PI / 8 || angle >= 15 * (M_PI / 8))
        return (EAST);
    if (angle >= 3 * M_PI / 8 && angle <= 5 * M_PI / 8)
        return (SOUTH);
    if (angle >= 7 * M_PI / 8 && angle <= 9 * M_PI / 8)
        return (WEST);
    if (angle >= 11 * M_PI / 8 && angle <= 13 * M_PI / 8)
        return (NORTH);
    if (angle > M_PI / 8 && angle < 3 * M_PI / 8)
        ret = SOUTH_EAST;
    if (angle > 5 * M_PI / 8 && angle < 7 * M_PI / 8)
        ret = SOUTH_WEST;
    if (angle > 9 * M_PI / 8 && angle < 11 * M_PI / 8)
        ret = NORTH_WEST;
    if (angle > 13 * M_PI / 8 && angle < 15 * M_PI / 8)
        ret = NORTH_EAST;
    if (check_wall_door(game, ret, mapx, mapy))
        return (ret);
    return (0);
}

int door_dir_x(int dir, int mapx)
{
    if (dir == EAST || dir == SOUTH_EAST || dir == NORTH_EAST)
        return (mapx + 1);
    if (dir == WEST || dir == SOUTH_WEST || dir == NORTH_WEST)
        return (mapx - 1);
    return (mapx);
}

int door_dir_y(int dir, int mapy)
{
    if (dir == SOUTH || dir == SOUTH_EAST || dir == SOUTH_WEST)
        return (mapy + 1);
    if (dir == NORTH || dir == NORTH_EAST || dir == NORTH_WEST)
        return (mapy - 1);
    return (mapy);
}

t_door_pos *check_door(t_game *game, int mapx, int mapy)
{
    t_door_pos  *door;
    door = malloc(sizeof(t_door_pos));
	if (!door)
		mlx_free(game, MALLOC_ERROR);
    int dir = cardinal_direction(game, mapx, mapy);
    if (dir == 0)
    {
        door->valid = 0;
        return (door);
    }
    door->x = door_dir_x(dir, mapx);
    door->y = door_dir_y(dir, mapy);
    if (game->map[door->y][door->x] == 'D' || game->map[door->y][door->x] == 'd')
        door->valid = 1;
    else
        door->valid = 0;
    printf("door %d %d\n", door->x, door->y);
    printf("valid %d\n", door->valid);
    return (door);
}

void    shoazw_map(t_game *game)
{
    int i = 0;
    while (game->map[i])
    {
        printf("%s\n", game->map[i]);
        i++;
    }
}
void	open_close_door(t_game *game)
{
	int	x;
	int	y;
	t_door_pos *door;

	x = game->player->pos_x / game->width;
	y = game->player->pos_y / game->height;
	door = check_door(game, x, y);
    shoazw_map(game);
    printf("-----------------\n");
	if (door->valid)
	{
        printf("%c\n", game->map[door->y][door->x]);
		if (game->map[door->y][door->x] == 'D')
			game->map[door->y][door->x] = 'd';
		else
			game->map[door->y][door->x] = 'D';
        printf("%c\n", game->map[door->y][door->x]);
	}
    shoazw_map(game);
}
