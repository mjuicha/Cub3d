#include "cub3d.h"

void	pl(t_game *game)
{
	int x = game->player->pos_x;
	int y = game->player->pos_y;
	int r = 10;
	int i = -r;
	int j = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				mlx_pixel_put(game->mlx, game->mlx_win, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}

void	cast_ray(t_game *game, double angle)
{
	double x = game->player->pos_x;
	double y = game->player->pos_y;
	double dx = cos(angle);
	double dy = sin(angle);
	int map_x, map_y;
	while (1)
	{
		x += dx;
		y += dy;
		map_x = (int)x / game->width;
		map_y = (int)y / game->height;
		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
			break;
		if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
			break;
		mlx_pixel_put(game->mlx, game->mlx_win, (int)x, (int)y, GREEN);
	}
}

void	eye(t_game *game)
{
	cast_ray(game, game->player->angle);
}

void    player(t_game *game)
{
    pl(game);
	eye(game);
	// printf("angle: %f\n", game->player->angle);
	// printf("pos_x: %d\n", game->player->pos_x);
	// printf("pos_y: %d\n", game->player->pos_y);
	// printf("move_speed: %f\n", game->player->move_speed);
	// printf("rot_speed: %f\n", game->player->rot_speed);
}