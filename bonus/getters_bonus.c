/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:53:00 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 16:52:32 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_top_pixel(double wall_height)
{
	int	top_pixel;

	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	return (top_pixel);
}

int	get_bottom_pixel(double wall_height)
{
	int	bottom_pixel;

	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	return (bottom_pixel);
}

double	get_wall_height(t_game *game, int ray)
{
	double	dis_pro;
	double	c_dis;
	double	wall_height;

	dis_pro = (WIDTH / 2) / tan(game->player->fov / 2);
	c_dis = game->dis[ray] * cos(game->t_angle[ray] - game->player->angle);
	wall_height = (game->height / c_dis) * dis_pro;
	return (wall_height);
}
