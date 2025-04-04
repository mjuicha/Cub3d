/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:43 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/01 11:57:05 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cardinal_direction(t_game *game, int mapx, int mapy)
{
	double	angle;
	int		ret;

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

int	door_dir_x(int dir, int mapx)
{
	if (dir == EAST || dir == SOUTH_EAST || dir == NORTH_EAST)
		return (mapx + 1);
	if (dir == WEST || dir == SOUTH_WEST || dir == NORTH_WEST)
		return (mapx - 1);
	return (mapx);
}

int	door_dir_y(int dir, int mapy)
{
	if (dir == SOUTH || dir == SOUTH_EAST || dir == SOUTH_WEST)
		return (mapy + 1);
	if (dir == NORTH || dir == NORTH_EAST || dir == NORTH_WEST)
		return (mapy - 1);
	return (mapy);
}
