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

void    update_position(t_game *game)
{
    game->player->pos_x += game->player->walk_dir * cos(game->player->angle) * game->player->move_speed;
    game->player->pos_y += game->player->walk_dir * sin(game->player->angle) * game->player->move_speed;
    game->player->pos_x += game->player->side_dir * cos(game->player->angle + M_PI_2) * game->player->move_speed;
    game->player->pos_y += game->player->side_dir * sin(game->player->angle + M_PI_2) * game->player->move_speed;
    game->player->angle += game->player->turn_dir * game->player->rot_speed;
    if (game->player->turn_dir != 0 || game->player->walk_dir != 0 || game->player->side_dir != 0)
    {
        printf("--------------------------------------------------\n");
        printf("x: %f\n", game->player->pos_x);
        printf("y: %f\n", game->player->pos_y);
        printf("angle: %f\n", game->player->angle);
        printf("Radian: %f\n", game->player->angle * 180 / M_PI);
    }
}

int    render_game(t_game *game)
{
    update_position(game);
    mlx_clear_window(game->mlx, game->mlx_win);
    draw_walls(game);
    player(game);
    return (0);
}