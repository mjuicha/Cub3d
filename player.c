#include "cub3d.h"

void	pl(t_game *game)
{
	int x = game->player->pos_x;
	int y = game->player->pos_y;
	int r = 10;
	int i = 0;
	int j = 0;
	while (i < 2 * r)
	{
		j = 0;
		while (j < 2 * r)
		{
			if ((i - r) * (i - r) + (j - r) * (j - r) <= r * r)
				mlx_pixel_put(game->mlx, game->mlx_win, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}

void    player(t_game *game)
{
    pl(game);
	printf("angle: %d\n", game->player->angle);
	printf("pos_x: %d\n", game->player->pos_x);
	printf("pos_y: %d\n", game->player->pos_y);
	printf("move_speed: %d\n", game->player->move_speed);
	printf("rot_speed: %d\n", game->player->rot_speed);
}