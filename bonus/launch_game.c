/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:23:51 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/04 17:04:00 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_floor_ceiling(t_game *game, int ray)
{
	int	y;

	y = 0;
	while (y < game->t_pix)
	{
		put_pixel_to_img(game, ray, y, game->ceiling);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel_to_img(game, ray, y, game->floor);
		y++;
	}
}

void	get_xoffset(t_game *game, int ray)
{
	if (game->is_hor[ray])
	{
		game->xoff = (int)game->wallx[ray] % game->width;
		game->off = 1;
	}
	else
	{
		game->xoff = (int)game->wally[ray] % game->height;
		game->off = 0;
	}
}

void	wall_projection(t_game *game)
{
	double	wall_height;
	int		y;
	int		dft;
	int		ray;

	ray = 0;
	while (ray < WIDTH)
	{
		spec_case(game, ray);
		wall_height = get_wall_height(game, ray);
		game->t_pix = get_top_pixel(wall_height);
		game->b_pix = get_bottom_pixel(wall_height);
		color_floor_ceiling(game, ray);
		y = game->t_pix;
		get_xoffset(game, ray);
		while (y < game->b_pix)
		{
			dft = y + (wall_height / 2) - HEIGHT / 2;
			game->yoff = dft * game->height / wall_height;
			put_pixel_to_img(game, ray, y, get_coloor(game,
					game->xoff, game->yoff, ray));
			y++;
		}
		ray++;
	}
}

void	is_walking(t_game *game, void **img)
{
	static int frame = 0;

	if (frame < 10)
		*img = game->sprite->img1->img;
	else
		*img = game->sprite->img2->img;
	frame++;
	if (frame == 20)
		frame = 0;
}

void	player_attack(t_game *game, void **img)
{
	static int frame = 0;
	// int		speed = 5;
	printf("frame = %d\n", frame);
	if (!frame)
		*img = game->sprite->img1->img;
	else if (frame <= 3)
		*img = game->sprite->img2->img;
	else if (frame <= 6)
		*img = game->sprite->img3->img;
	else if (frame <= 9)
		*img = game->sprite->img4->img;
	else if (frame <= 12)
		*img = game->sprite->img5->img;
	else if (frame <= 15)
		*img = game->sprite->img6->img;
	else if (frame <= 18)
		*img = game->sprite->img7->img;
	else if (frame <= 21)
		*img = game->sprite->img8->img;
	else if (frame <= 24)
		*img = game->sprite->img9->img;
	else if (frame <= 27)
		*img = game->sprite->img10->img;
	else if (frame <= 30)
		*img = game->sprite->img14->img;
	else if (frame <= 33)
		*img = game->sprite->img15->img;
	else if (frame <= 36)
		*img = game->sprite->img16->img;
	else if (frame <= 39)
		*img = game->sprite->img17->img;
	else if (frame <= 42)
		*img = game->sprite->img18->img;
	else if (frame <= 45)
		*img = game->sprite->img19->img;
	else if (frame <= 48)
		*img = game->sprite->img20->img;
	frame++;
	if (frame == 48)
	{
		frame = 0;
		game->is_fighting = 0;
	}
}

void	animated_sprite(t_game *game)
{
	void	*img = NULL; 
	if (game->is_fighting)
		player_attack(game, &img);
	else if (game->player->walk_dir)
		is_walking(game, &img);
	else
		img = game->sprite->img1->img;
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, 140, 320);
}

int	render_game(t_game *game)
{
	update_position(game);
	fov(game);
	wall_projection(game);
	mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_win->img, 0, 0);
	animated_sprite(game);
	// 10 is nothing
	
	
	return (0);
}
