/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:23:49 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/21 16:19:26 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_player(t_game *game)
{
	game->player->angle += game->player->turn_dir * game->player->rot_speed;
}

int	is_wall(t_game *game, double next_x, double next_y)
{
	int	mapx;
	int	mapy;

	mapx = (int)(next_x / game->height);
	mapy = (int)(next_y / game->width);
	if (mapx < 0 || mapy < 0 || mapy >= game->mapcounter
		|| mapx >= (int)ft_strlen(game->map[mapy]))
		return (1);
	if (game->map[mapy][mapx] == ' ')
		return (1);
	return (game->map[mapy][mapx] == '1');
}

void	walk_direct(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player->pos_x + game->player->walk_dir
		* cos(game->player->angle) * game->player->move_speed;
	next_y = game->player->pos_y + game->player->walk_dir
		* sin(game->player->angle) * game->player->move_speed;
	if (!is_wall(game, next_x + CT, next_y + CT)
		&& !is_wall(game, next_x - CT, next_y - CT))
	{
		game->player->pos_x = next_x;
		game->player->pos_y = next_y;
	}
}

void	side_direct(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player->pos_x + game->player->side_dir
		* cos(game->player->angle + M_PI_2) * game->player->move_speed;
	next_y = game->player->pos_y + game->player->side_dir
		* sin(game->player->angle + M_PI_2) * game->player->move_speed;
	if (!is_wall(game, next_x + CT, next_y + CT)
		&& !is_wall(game, next_x - CT, next_y - CT))
	{
		game->player->pos_x = next_x;
		game->player->pos_y = next_y;
	}
}

void	update_position(t_game *game)
{
	walk_direct(game);
	side_direct(game);
	turn_player(game);
}
