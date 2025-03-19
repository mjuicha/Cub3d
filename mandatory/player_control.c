/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:23:49 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 23:26:46 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game)
{
	int	pos_x;
	int	pos_y;
	int	mapx;
	int	mapy;

	pos_x = game->player->pos_x + game->player->walk_dir
		* cos(game->player->angle) * game->player->move_speed;
	pos_y = game->player->pos_y + game->player->walk_dir
		* sin(game->player->angle) * game->player->move_speed;
	pos_x += game->player->side_dir * cos(game->player->angle + M_PI_2)
		* game->player->move_speed;
	pos_y += game->player->side_dir * sin(game->player->angle + M_PI_2)
		* game->player->move_speed;
	mapx = pos_x / game->width;
	mapy = pos_y / game->height;
	if (game->map[mapy][mapx] && game->map[mapy][mapx] == '1')
		return (1);
	return (0);
}

void	turn_player(t_game *game)
{
	game->player->angle += game->player->turn_dir * game->player->rot_speed;
}

void	walk_direct(t_game *game)
{
	if (!is_wall(game))
	{
		game->player->pos_x += game->player->walk_dir
			* cos(game->player->angle) * game->player->move_speed;
		game->player->pos_y += game->player->walk_dir
			* sin(game->player->angle) * game->player->move_speed;
	}
}

void	side_direct(t_game *game)
{
	if (!is_wall(game))
	{
		game->player->pos_x += game->player->side_dir
			* cos(game->player->angle + M_PI_2) * game->player->move_speed;
		game->player->pos_y += game->player->side_dir
			* sin(game->player->angle + M_PI_2) * game->player->move_speed;
	}
}

void	update_position(t_game *game)
{
	walk_direct(game);
	side_direct(game);
	turn_player(game);
}
