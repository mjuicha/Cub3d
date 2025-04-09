/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:36:36 by librahim          #+#    #+#             */
/*   Updated: 2025/04/09 18:37:39 by mjuicha          ###   ########.fr       */
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

int	render_game(t_game *game)
{
	update_position(game);
	cast_all_rays(game);
	wall_projection(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_win->img, 0, 0);
	return (0);
}
