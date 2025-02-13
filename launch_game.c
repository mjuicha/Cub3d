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
void    put_pixel_to_img(t_game *game, int x, int y, int color);
void    reset_color(t_game *game)
{
    uint32_t    color = BLACK;
    int x = 0;
    int y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            put_pixel_to_img(game, x, y, color);
            x++;
        }
        y++;
    }
}


void    update_position(t_game *game)
{
    game->player->pos_x += game->player->walk_dir * cos(game->player->angle) * game->player->move_speed;
    game->player->pos_y += game->player->walk_dir * sin(game->player->angle) * game->player->move_speed;
    game->player->pos_x += game->player->side_dir * cos(game->player->angle + M_PI_2) * game->player->move_speed;
    game->player->pos_y += game->player->side_dir * sin(game->player->angle + M_PI_2) * game->player->move_speed;
    game->player->angle += game->player->turn_dir * game->player->rot_speed;
    // if (game->player->walk_dir || game->player->side_dir || game->player->turn_dir)
    //     reset_color(game);
}

void    put_pixel_to_img(t_game *game, int x, int y, int color)
{
    char    *dst;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}
void	wall_projection(t_game *game)
{
    int ray = 0;
    while (ray < WIDTH)
    {
        if (game->is_spec[ray] && game->is_hor[ray] && (!game->is_hor[ray - 1] || !game->is_hor[ray + 1]))
            game->is_hor[ray] = 0;
	    double	dis_pro = (WIDTH / 2) / tan(FOV / 2);
        double  c_dis = game->dis[ray] * cos(game->t_angle[ray] - game->player->angle);
	    double wall_height = (game->height / c_dis) * dis_pro;
	    game->b_pix = (HEIGHT / 2) + (wall_height / 2);
	    game->t_pix = (HEIGHT / 2) - (wall_height / 2);
	    if (game->b_pix > HEIGHT)
	    	game->b_pix = HEIGHT;
	    if (game->t_pix < 0)
    		game->t_pix = 0;
        int y = 0;
        while (y < game->t_pix)
        {
            put_pixel_to_img(game, ray, y, SKY_BLUE);
            y++;
        }
        while (y < game->b_pix)
        {
            put_pixel_to_img(game, ray, y, !game->is_hor[ray] ? WHITE : RED);
            y++;
        }
        while (y < HEIGHT)
        {
            put_pixel_to_img(game, ray, y, FLOOR);
            y++;
        }
        ray++;
    }
}

void    draw_color(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}

int    render_game(t_game *game)
{
    reset_color(game);
    update_position(game);
    player(game);
    wall_projection(game);
	game->player->fetch = 1;
    draw_color(game);
    return (0);
}