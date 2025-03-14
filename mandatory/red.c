#include "cub3d.h"

void    wall(t_game *game, int x, int y, void *wall)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, wall, x, y);
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

int	is_wall(t_game *game)
{
	int pos_x;
	int pos_y;
	pos_x = game->player->pos_x + game->player->walk_dir * cos(game->player->angle) * game->player->move_speed;
	pos_y = game->player->pos_y + game->player->walk_dir * sin(game->player->angle) * game->player->move_speed;
	pos_x += game->player->side_dir * cos(game->player->angle + M_PI_2) * game->player->move_speed;
	pos_y += game->player->side_dir * sin(game->player->angle + M_PI_2) * game->player->move_speed;
	int mapx;
	int mapy;
	mapx = pos_x / game->width;
	mapy = pos_y / game->height;        
	if (game->map[mapy][mapx] && game->map[mapy][mapx] == '1')
		return (1);
	return (0);
}

void	turn_player(t_game *game)
{
	game->player->angle += game->player->turn_dir * game->player->rot_speed;
}

void walk_direct(t_game *game)
{
    if (!is_wall(game))
    {
        game->player->pos_x += game->player->walk_dir * cos(game->player->angle) * game->player->move_speed;
        game->player->pos_y += game->player->walk_dir * sin(game->player->angle) * game->player->move_speed;
    }
}
void	side_direct(t_game *game)
{
	if (!is_wall(game))
	{
		game->player->pos_x += game->player->side_dir * cos(game->player->angle + M_PI_2) * game->player->move_speed;
		game->player->pos_y += game->player->side_dir * sin(game->player->angle + M_PI_2) * game->player->move_speed;
	}
}
void	update_position(t_game *game)
{
	walk_direct(game);
	side_direct(game);
	turn_player(game);
}

void    put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char    *dst;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}


int	is_nord(double angle)
{
	if (angle >= 0 && angle < M_PI)
		return (1);
	return (0);
}

int	is_east(double angle)
{
	if (angle >= M_PI_2 && angle < 3 * M_PI_2)
		return (1);
	return (0);
}

unsigned int	get_coloor(t_game *game, int x, int y, int ray)
{
	char	*dst;

	if (game->off)
	{
		if (is_nord(game->t_angle[ray]))
			dst = game->nord->addr + (y * game->nord->line_length + x * (game->nord->bpp / 8));
		else
			dst = game->south->addr + (y * game->south->line_length + x * (game->south->bpp / 8));
	}
	else
	{
		if (is_east(game->t_angle[ray]))
			dst = game->east->addr + (y * game->east->line_length + x * (game->east->bpp / 8));
		else
			dst = game->west->addr + (y * game->west->line_length + x * (game->west->bpp / 8));
	}
	return (*(unsigned int *)dst);
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
			put_pixel_to_img(game, ray, y, game->ceiling);
			y++;
		}
		int xoff;
		int yoff;
		if (game->is_hor[ray])
		{
			xoff = (int)game->wallx[ray] % game->width;
			game->off = 1;
		}
		else
		{
			xoff = (int)game->wally[ray] % game->height;
			game->off = 0;
		}
		while (y < game->b_pix)
		{
			int dft = y + (wall_height / 2) - HEIGHT / 2;
			yoff = dft * game->height / wall_height;
			put_pixel_to_img(game, ray, y, get_coloor(game, xoff, yoff, ray));
			y++;
		}
		while (y < HEIGHT)
		{
			put_pixel_to_img(game, ray, y, game->floor);
			y++;
		}
		ray++;
	}
}

void    draw_color(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}

char	*dir(t_game *game)
{
	if (game->player->angle >= 0 && game->player->angle < M_PI_2)
		return (BLACK_WALL);
	else if (game->player->angle >= M_PI_2 && game->player->angle < M_PI)
		return (BLACK_WALL);
	else if (game->player->angle >= M_PI && game->player->angle < 3 * M_PI_2)
		return (EMPTY_WALL);
	else
		return (EMPTY_WALL);
}



int    render_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	update_position(game);
	fov(game);
	wall_projection(game);
	game->player->fetch = 1;
	draw_color(game);
	return (0);
}

// void    draw_walls(t_game *game)
// {
//     int i = 0;
//     int j = 0;
//     int mx = 0;
//     int my = 0;
//     while (game->map[my])
//     {
//         j = 0;
//         mx = 0;
//         while (game->map[my][mx])
//         {
//             if (game->map[my][mx] == '1')
//                 wall(game, j, i, game->black_wall);
//             else if (game->map[my][mx] == '0' || game->map[my][mx] == 'P')
//                 wall(game, j, i, game->empty_wall);
//             j += game->width;
//             mx++;
//         }
//         i += game->height;
//         my++;
//     }
// }