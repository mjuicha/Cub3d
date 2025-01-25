#include "cub3d.h"

void    wall(t_game *game, int x, int y)
{
    int limit_x = x * TILE_SIZE;
    int limit_y = y * TILE_SIZE;
    int orx = x;
    int t = 0;

    while (x < limit_x)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y, GREY);
		t = y;
		while (t < limit_y)
			mlx_pixel_put(game->mlx, game->mlx_win, x, ++t, WHITE);
		mlx_pixel_put(game->mlx, game->mlx_win, x, limit_y, WHITE);
		x++;
	}
	x = orx;
	while (y < limit_y)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y, GREY);
		mlx_pixel_put(game->mlx, game->mlx_win, limit_x, y, GREY);
		y++;
	}
}

void    ground(t_game *game, int x, int y)
{
    int limit_x = x * TILE_SIZE;
    int limit_y = y * TILE_SIZE;
    int orx = x;
    int t = 0;

    while (x < limit_x)
    {
        mlx_pixel_put(game->mlx, game->mlx_win, x, y, GREY);
        t = y;
        while (t < limit_y)
            mlx_pixel_put(game->mlx, game->mlx_win, x, ++t, RED);
        mlx_pixel_put(game->mlx, game->mlx_win, x, limit_y, RED);
        x++;
    }
    x = orx;
    while (y < limit_y)
    {
        mlx_pixel_put(game->mlx, game->mlx_win, x, y, GREY);
        mlx_pixel_put(game->mlx, game->mlx_win, limit_x, y, GREY);
        y++;
    }
}

void    draw_walls(t_game *game)
{
    int i = 0;
    int j = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
                wall(game, j, i);
            else if (game->map[i][j] == '0')
                ground(game, j, i);
            j++;
        }
        i++;
    }
}
void    launch_game(t_game *game)
{
    draw_walls(game);
}