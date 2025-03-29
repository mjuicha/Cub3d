/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:57:28 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/29 02:44:57 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	printf("window closed\n");
	mlx_free(game, NULL);
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
		game->player->walk_dir = 1;
	else if (keycode == S)
		game->player->walk_dir = -1;
	else if (keycode == A)
		game->player->side_dir = -1;
	else if (keycode == D)
		game->player->side_dir = 1;
	else if (keycode == LEFT)
		game->player->turn_dir = -1;
	else if (keycode == RIGHT)
		game->player->turn_dir = 1;
	else if (keycode == SPACE)
		open_close_door(game);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == W || keycode == S)
		game->player->walk_dir = 0;
	else if (keycode == A || keycode == D)
		game->player->side_dir = 0;
	else if (keycode == LEFT || keycode == RIGHT)
		game->player->turn_dir = 0;
	return (0);
}

void	events_hook(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 0, key_pressed, game);
	mlx_hook(game->mlx_win, 3, 0, key_released, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
}
