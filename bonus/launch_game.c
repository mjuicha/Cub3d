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
	if (game->map[mapy][mapx] && game->map[mapy][mapx] == '1' || game->map[mapy][mapx] == 'D')
		return (1);
	return (0);
}

void	turn_player(t_game *game)
{
	game->player->angle += game->player->turn_dir * game->player->rot_speed;
	if (game->player->turn_dir)
		printf("angle is %f\n", game->player->angle * 180 / M_PI);
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

	if (game->is_door[ray])
		dst = game->addr5 + (y * game->line_length5 + x * (game->bpp5 / 8));
	else if (game->off)
	{
		if (is_nord(game->t_angle[ray]))
			dst = game->addr1 + (y * game->line_length1 + x * (game->bpp1 / 8));
		else
			dst = game->addr3 + (y * game->line_length3 + x * (game->bpp3 / 8));
	}
	else
	{
		if (is_east(game->t_angle[ray]))
			dst = game->addr2 + (y * game->line_length2 + x * (game->bpp2 / 8));
		else
			dst = game->addr4 + (y * game->line_length4 + x * (game->bpp4 / 8));
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
			put_pixel_to_img(game, ray, y, SKY_BLUE);
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

void	get_img2(t_game *game)
{
	game->blue_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[1], &game->width, &game->height);
	game->endian2 = malloc(sizeof(int));
	game->addr2 = mlx_get_data_addr(game->blue_wall, &game->bpp2, &game->line_length2, game->endian2);
}

void	get_img(t_game *game)
{
	game->black_wall = mlx_xpm_file_to_image(game->mlx, game->texture_path[0], &game->width, &game->height);
	game->endian1 = malloc(sizeof(int));
	game->addr1 = mlx_get_data_addr(game->black_wall, &game->bpp1, &game->line_length1, game->endian1);
}

void	get_sprite(t_game *game)
{
	static int	frame = 0;
	int			speed = 5; // Adjust this value to control the speed


	if (!game->set)
		game->gun = game->sprite;
	else if (frame++ % speed == 0)
	{
		if (1 == game->set)
			game->gun = game->sprite1;
		else if (2 == game->set)
			game->gun = game->sprite2;
		else if (3 == game->set)
			game->gun = game->sprite3;
		else if (4 == game->set)
			game->gun = game->sprite4;
		else if (5 == game->set)
			game->gun = game->sprite5;
		else if (6 == game->set)
			game->gun = game->sprite6;
		game->set++;
		if (game->set == 7)
			game->set = 0;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->gun, 385, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->warning, 338, 590);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->aim, WIDTH / 2 - 25, HEIGHT / 2 - 25);
	// mlx_string_put(game->mlx, game->mlx_win, 385, 650, 0x00FF0000, "25 Shots Left");
}

void	mini_map(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->circle, 0, 0);
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
	get_sprite(game);
	mini_map(game);
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