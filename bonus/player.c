/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:01 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 14:16:52 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_waaal(t_game *game, int indice)
{
	int	x;
	int	y;

	if (indice)
	{
		x = floor(game->hor_x_intercept / game->width);
		y = floor((game->hor_y_intercept + is_up(game)) / game->height);
	}
	else
	{
		x = floor((game->ver_x_intercept + is_left(game)) / game->width);
		y = floor(game->ver_y_intercept / game->height);
	}
	if (x < 0 || y < 0 || y >= game->mapcounter \
		|| x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] && (game->map[y][x] == '1' || game->map[y][x] == 'D'))
		return (1);
	return (0);
}

double	hoz(t_game *game, double angle)
{
	double	y_step;
	double	x_step;

	game->hor_y_intercept = (floor(game->player->pos_y / game->height)
			* game->height) + is_down(game);
	game->hor_x_intercept = game->player->pos_x + ((game->hor_y_intercept
				- game->player->pos_y) / tan(angle));
	y_step = game->height;
	if (game->player->dir->up)
		y_step *= -1;
	x_step = game->height / tan(angle);
	if ((game->player->dir->left && x_step > 0)
		|| (game->player->dir->right && x_step < 0))
		x_step *= -1;
	while (1)
	{
		if (check_waaal(game, 1))
			break ;
		game->hor_x_intercept += x_step;
		game->hor_y_intercept += y_step;
	}
	return (phitagore(game, game->hor_x_intercept, game->hor_y_intercept));
}

double	ver(t_game *game, double angle)
{
	double	y_step;
	double	x_step;

	game->ver_x_intercept = (floor(game->player->pos_x / game->width)
			* game->width) + is_right(game);
	game->ver_y_intercept = game->player->pos_y + ((game->ver_x_intercept
				- game->player->pos_x) * tan(angle));
	x_step = game->width;
	if (game->player->dir->left)
		x_step *= -1;
	y_step = game->width * tan(angle);
	if ((game->player->dir->up && y_step > 0)
		|| (game->player->dir->down && y_step < 0))
		y_step *= -1;
	while (1)
	{
		if (check_waaal(game, 0))
			break ;
		game->ver_x_intercept += x_step;
		game->ver_y_intercept += y_step;
	}
	return (phitagore(game, game->ver_x_intercept, game->ver_y_intercept));
}

void	cast_one_ray(t_game *game, double angle, int ray)
{
	double	h_dis;
	double	v_dis;

	angle = normalize_angle(angle);
	game->player->dir = get_ray_direction(game, angle);
	h_dis = hoz(game, angle);
	v_dis = ver(game, angle);
	game->dis[ray] = shortest_dist(h_dis, v_dis, h_dis, v_dis);
	game->wallx[ray] = shortest_dist(h_dis, v_dis,
			game->hor_x_intercept, game->ver_x_intercept);
	game->wally[ray] = shortest_dist(h_dis, v_dis,
			game->hor_y_intercept, game->ver_y_intercept);
	game->t_angle[ray] = angle;
	game->is_hor[ray] = inf_equal(h_dis, v_dis);
	is_door(game, ray);
	free(game->player->dir);
	game->is_spec[ray] = equal(h_dis, v_dis);
}

void	cast_all_rays(t_game *game)
{
	float	angleofray;
	int		i;

	i = 0;
	angleofray = game->player->angle - (game->player->fov / 2);
	while (i < WIDTH)
	{
		cast_one_ray(game, angleofray, i);
		angleofray += game->player->fov / WIDTH;
		i++;
	}
}
