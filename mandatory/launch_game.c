/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:23:51 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/18 18:24:49 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall(t_game *game, int x, int y, void *wall)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, wall, x, y);
}

int	is_wall(t_game *game)
{
	int	pos_x;
	int	pos_y;

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

void	walk_direct(t_game *game)
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

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img_win->addr + (y * game->img_win->line_length + x * (game->img_win->bpp / 8));
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

void	wall_projection(t_game *game)
{
	int	ray;

	ray = 0;
	while (ray < WIDTH)
	{
		if (game->is_spec[ray] && game->is_hor[ray] && (!game->is_hor[ray - 1] || !game->is_hor[ray + 1]))
			game->is_hor[ray] = 0;
		double	dis_pro = (WIDTH / 2) / tan(game->player->fov / 2);
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
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_win->img, 0, 0);
}

int	render_game(t_game *game)
{
	update_position(game);
	fov(game);
	wall_projection(game);
	game->player->fetch = 1;
	draw_color(game);
	return (0);
}
