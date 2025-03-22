/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:23:49 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 12:11:02 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game_data *game, double next_x, double next_y)
{
	int	mapx;
	int	mapy;

	mapx = next_x / game->height;
	mapy = next_y / game->width;
	if (mapx < 0 || mapy < 0 || mapy >= game->mapcounter
		|| mapx >= (int)ft_strlen(game->map[mapy]))
		return (1);
	if (game->map[mapy][mapx] == ' ')
		return (1);
	return (game->map[mapy][mapx] == '1');
}

void	walk_direct(t_game_data *game)
{
	int	next_player_x;
	int	next_player_y;

	next_player_x = game->player->pos_x + game->player->walk_dir
		* cos(game->player->angle) * game->player->move_speed;
	next_player_y = game->player->pos_y + game->player->walk_dir
		* sin(game->player->angle) * game->player->move_speed;
	if (!is_wall(game, next_player_x + CT, next_player_y + CT)
		&& !is_wall(game, next_player_x - CT, next_player_y - CT))
	{
		game->player->pos_x = next_player_x;
		game->player->pos_y = next_player_y;
	}
}

void	side_direct(t_game_data *game)
{
	int	next_player_x;
	int	next_player_y;

	next_player_x = game->player->pos_x + game->player->side_dir
		* cos(game->player->angle + M_PI_2) * game->player->move_speed;
	next_player_y = game->player->pos_y + game->player->side_dir
		* sin(game->player->angle + M_PI_2) * game->player->move_speed;
	if (!is_wall(game, next_player_x + CT, next_player_y + CT)
		&& !is_wall(game, next_player_x - CT, next_player_y - CT))
	{
		game->player->pos_x = next_player_x;
		game->player->pos_y = next_player_y;
	}
}

void	update_position(t_game_data *game)
{
	walk_direct(game);
	side_direct(game);
	game->player->angle += game->player->turn_dir * game->player->rot_speed;
}
