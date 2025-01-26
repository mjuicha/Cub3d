#include "cub3d.h"

void    wall(t_game *game, int x, int y, void *wall)
{
    mlx_put_image_to_window(game->mlx, game->mlx_win, wall, x, y);
}

void    draw_walls(t_game *game)
{
    int i = 0;
    int j = 0;
    int mx = 0;
    int my = 0;
    while (game->map[my])
    {
        j = 0;
        mx = 0;
        while (game->map[my][mx])
        {
            if (game->map[my][mx] == '1')
                wall(game, j, i, game->black_wall);
            else if (game->map[my][mx] == '0' || game->map[my][mx] == 'P')
                wall(game, j, i, game->empty_wall);
            j += game->width;
            mx++;
        }
        i += game->height;
        my++;
    }
}
void    launch_game(t_game *game)
{
    draw_walls(game);
}