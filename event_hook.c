#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	printf("window closed\n");
	exit(0);
}

int	keys(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
	{
        game->player->pos_x += cos(game->player->angle) * game->player->move_speed;
        game->player->pos_y += sin(game->player->angle) * game->player->move_speed;
    }
	else if (keycode == S)
    {
		game->player->pos_x -= cos(game->player->angle) * game->player->move_speed;
        game->player->pos_y -= sin(game->player->angle) * game->player->move_speed;
    }
	else if (keycode == A)
    {
        game->player->pos_x -= cos(game->player->angle + M_PI_2) * game->player->move_speed;
        game->player->pos_y -= sin(game->player->angle + M_PI_2) * game->player->move_speed;
    }
	else if (keycode == D)
    {
        game->player->pos_x += cos(game->player->angle + M_PI_2) * game->player->move_speed;
        game->player->pos_y += sin(game->player->angle + M_PI_2) * game->player->move_speed;
    }
    if (keycode == LEFT || keycode == RIGHT)
    {
        if (keycode == LEFT)
		    game->player->angle -= game->player->rot_speed;
        if (keycode == RIGHT)
		    game->player->angle += game->player->rot_speed;
        if (game->player->angle < 0)
            game->player->angle += 2 * M_PI;
        if (game->player->angle > 2 * M_PI)
            game->player->angle -= 2 * M_PI;
    }
	mlx_clear_window(game->mlx, game->mlx_win);
	draw_walls(game);
	player(game);
	return (0);
}

void	events_hook(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 0, keys, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
}