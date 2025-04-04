/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:57:28 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/04 16:57:52 by mjuicha          ###   ########.fr       */
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
	else if (keycode == M)
	{
		game->is_fighting = 1;
		printf("fighting\n");
	}
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

int mouse_move(int x, int y, t_game *game)
{
    static int	old_mouse_x = 0;
    int 		diff;
    float		turn_scale;
	(void)y;

    if (x != old_mouse_x)
    {
        diff = abs(x - old_mouse_x);
        turn_scale = 180.0f / 2560;
        if (x > old_mouse_x)
            game->player->turn_dir = turn_scale;
        else
            game->player->turn_dir = -turn_scale;
        while (diff--)
            turn_player(game);
        game->player->turn_dir = 0;
    }
    old_mouse_x = x;
    return 0;
}

int	fighting(int keycode, t_game *game)
{
	if (keycode == 1)
{	game->is_fighting = 1;
	printf("fighting\n");
	
}		
	return (0);
}

void	events_hook(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 0, key_pressed, game);
	mlx_hook(game->mlx_win, 3, 0, key_released, game);
	mlx_hook(game->mlx_win, 6, 0, mouse_move, game);
	// mlx_mouse_hook(game->mlx_win, fighting, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
}
